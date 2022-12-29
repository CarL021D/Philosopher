/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:40 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/28 13:03:35 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	launch_philo_routine(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_create(&philo->thread, NULL, (void*)&philo_routine, philo);
		philo = philo->next;
		i++;
	}
	// Usleep to avoid creating a mutex for the data->nb_of_philos variable 
	usleep(40);
}

int		option(t_philo *philo)
{

}

void	philo_routine(t_philo *philo)
{ 
	// todo: - func exec routine for one philo
	if (philo->data->nb_of_philos % 2 == 0)
		desync_action_for_even_philo_count(philo);
	else
		desync_action_for_odd_philo_count(philo);
	option = philo->data->max_meal_option;
	while (!philo_died(philo) || (option(philo) && !all_philo_full(philo)))
	{
		if (!philo_died(philo) || (option(philo) && !all_philo_full(philo)))
			philo_is_eating(philo);
		if (!philo_died(philo) || (option && !all_philo_full(philo)))
			philo_is_sleeping(philo);
		if (!philo_died(philo) || (option && !all_philo_full(philo)))
			philo_is_thinking(philo);
		usleep(100);
	}
}

void	stop_routine_if_philo_dead_or_full(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = *philo_lst;
	while (!philo_died(philo) || !all_philo_full(philo))
	{
		philo = *philo_lst;
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (kill_philo_if_possible(philo)
				|| stop_routine_if_all_philo_full(philo, data))
					return ;
			i++;
			philo = philo->next;
		}
	}
}

int main(int ac, char **av)
{
	t_philo		*philo;
	t_data		data;

	if (exit_if_args_errors(ac, av) == ERROR)
		return (1);
	if (init_data(&philo, &data, ac, av) == ERROR)
		return (1);
	launch_philo_routine(&philo, &data);
	stop_routine_if_philo_dead_or_full(&philo, &data);
	if (destroy_threads(&philo, &data) == ERROR)
		return (1);
	destroy_mutex(&philo, &data);
	free_circular_linked_list(&philo, &data);
}

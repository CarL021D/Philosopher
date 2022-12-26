/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:23:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/26 18:24:56 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_routine(t_philo *philo)
{
	int		option;
 
	if (philo->data->nb_of_philos % 2 == 0)
		desync_action_for_even_philo_count(philo);
	else
		desync_action_for_odd_philo_count(philo);
	option = philo->data->max_meal_option;

	while (!philo_died(philo) || (option && !max_nb_of_meals_reached(philo)))
	{
		if (!philo_died(philo) || (option && !max_nb_of_meals_reached(philo)))
			philo_is_eating(philo);
		if (!philo_died(philo) || (option && !max_nb_of_meals_reached(philo)))
			philo_is_sleeping(philo);
		if (!philo_died(philo) || (option && !max_nb_of_meals_reached(philo)))
			philo_is_thinking(philo);
		usleep(100);
	}
}

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
}

void	stop_routine_if_philo_dead_or_full(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			option;
	int			i;

	philo = *philo_lst;
	option = philo->data->max_meal_option;
	while (!philo_died(philo) || (option && !max_nb_of_meals_reached(philo)))
	{
		philo = *philo_lst;
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (kill_philo_if_possible(philo) == TRUE)
				return ;
			if (stop_routine_if_all_philo_full(philo, data))
				return ;
			i++;
			philo = philo->next;
		}
	}
}
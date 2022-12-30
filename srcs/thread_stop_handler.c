/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stop_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:23:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/30 17:26:13 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == true)
	{
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	return (false);
}

int		all_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->every_philo_full_mutex);
	if (philo->data->max_meal_option == false)
	{
		pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
		return (false);
	}
	if (philo->data->every_philo_full == true)
	{
		pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	return (false);
}





int		kill_philo_if_possible(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		pthread_mutex_lock(&philo->data->philo_has_died_mutex);
		philo->data->philo_has_died = true;
		mutex_print(philo, "died\n");
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	return (false);
}


int		try_to_set_all_philo_to_full(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (philo->total_meals_eaten < philo->data->max_nb_of_meals)
			return (false);
		i++;
		philo = philo->next;
	}
	pthread_mutex_lock(&philo->data->every_philo_full_mutex);
	data->every_philo_full = true;
	pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	return (true);
}
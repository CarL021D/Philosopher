/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stop_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:23:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/28 13:02:02 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == TRUE)
	{
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	return (FALSE);
}

int		all_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	if (philo->data->max_meal_option == FALSE)
	{
		pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
		return (FALSE);
	}
	if (philo->data->every_philo_full == TRUE)
	{
		pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	return (FALSE);
}





int		kill_philo_if_possible(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		pthread_mutex_lock(&philo->data->philo_has_died_mutex);
		philo->data->philo_has_died = TRUE;
		mutex_print(philo, "died\n");
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	return (FALSE);
}


int		stop_routine_if_all_philo_full(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	// pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	while (i < data->nb_of_philos)
	{
		if (philo->total_meals_eaten < philo->data->max_nb_of_meals)
		{
			// pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
			return (FALSE);
		}
		i++;
		philo = philo->next;
	}
	// pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	data->every_philo_full = TRUE;
	pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	return (TRUE);
}
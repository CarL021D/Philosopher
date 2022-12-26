/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:55 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/26 18:26:33 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

void	desync_action_for_even_philo_count(t_philo *philo)
{
	if (philo->index % 2)
		usleep(philo->data->time_to_eat * 1000);
}

void	desync_action_for_odd_philo_count(t_philo *philo)
{
	int		time;

	if (philo->data->nb_of_philos == 1)
		return ;
	if (philo->index == philo->data->nb_of_philos)
		time = (philo->data->time_to_eat * 2);
	if (philo->index % 2 == 0)
		time = philo->data->time_to_eat;
	usleep(time * 1000);
}

int	ft_atoi(const char *nptr)
{
	long long   res;
	int	sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	return (sign * res);
}
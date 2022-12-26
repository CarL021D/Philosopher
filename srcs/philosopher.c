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




int		max_nb_of_meals_reached(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	if (philo->data->every_philo_full == TRUE)
	{
		pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	return (FALSE);
}

int		stop_routine_if_all_philo_full(t_philo *philo, t_data *data)
{
	int		i;

	if (!philo->data->max_meal_option)
		return (FALSE);
	i = 0;
	pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	while (i < data->nb_of_philos)
	{
		if (philo->total_meals_eaten < philo->data->max_nb_of_meals)
		{
			pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
			return (FALSE);
		}
		i++;
		philo = philo->next;
	}
	pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	return (TRUE);
}





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
			// kill_philo_if_possible(philo);
			// pthread_mutex_lock(&data->philo_has_died_mutex);
			// if (data->philo_has_died == TRUE)
			// {
			// 	pthread_mutex_unlock(&data->philo_has_died_mutex);
			// 	return ;
			// }
			// pthread_mutex_unlock(&data->philo_has_died_mutex);
			// stop_routine_if_all_philo_full(philo, data);
			// pthread_mutex_lock(&data->max_nb_of_meals_mutex);
			// if (data->every_philo_full == TRUE)
			// {
			// 	pthread_mutex_unlock(&data->philo_has_died_mutex);
			// 	return ;
			// }
			// pthread_mutex_unlock(&data->max_nb_of_meals_mutex);
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

#include "philosopher.h"

long    get_current_time(void)
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
	// int		time;

	// time = philo->time_to_eat;
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

// void	philo_action_desync(t_philo *philo)
// {
// 	int		time;

// 	if (philo->data->nb_of_philos % 2 == 0)
// 		desync_action_for_even_philo_count(philo);
// 	else
// 		desync_action_for_odd_philo_count(philo);
// 	while (philo->data->philo_has_died == FALSE)
// 	{
// 		philo_is_eating(philo);
// 		philo_is_sleeping(philo);
// 		philo_is_thinking(philo);
// 	}
// }

int		max_nb_of_meals_reached(t_philo *philo)
{
	int		end_exec;

	pthread_mutex_lock(&philo->data->max_nb_of_meals_mutex);
	if (philo->total_meals_eaten < philo->data->max_nb_of_meals)
		end_exec = FALSE;
	else
		end_exec = TRUE;
	philo->data->max_nb_of_meals = end_exec;
	pthread_mutex_unlock(&philo->data->max_nb_of_meals_mutex);
	return (end_exec);
}

void	philo_routine(t_philo *philo)
{
	// philo_action_desync(philo);
	if (philo->data->nb_of_philos % 2 == 0)
		desync_action_for_even_philo_count(philo);
	else
		desync_action_for_odd_philo_count(philo);
	// Infinite loop ???
	while (philo->data->philo_has_died == FALSE || max_nb_of_meals_reached(philo) == FALSE)
	{
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
	}

}

void	launch_philo_routine(t_data *data, t_philo **lst_philo)
{
	t_philo		*philo;
	int		i;

	philo = *lst_philo;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_create(&philo->thread, NULL, (void*)&philo_routine, philo);
		philo = philo->next;
		i++;
	}
}


int main(int ac, char **av)
{
	t_data      data;
	t_philo     *philo;

	if (exit_if_args_errors(ac, av) == ERROR)
		return (1);
	if (init_data(&data, &philo, ac, av) == ERROR)
		return (1);
	launch_philo_routine(&data, &philo);
}

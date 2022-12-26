#include "philosopher.h"

void	mutex_print(t_philo *philo, char *message)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->lock_print);
	current_time = get_current_time() - philo->data->launch_time;
	printf("%ld - %d %s\n", current_time, philo->index, message);
	pthread_mutex_unlock(&philo->data->lock_print);
}

// TODO: - Check condition for max meal reached for an individual philo 

void    philo_is_eating(t_philo *philo)
{
	int     time;
	int		option;

	time = philo->data->time_to_eat;
	option = philo->data->max_meal_option;
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (!philo->data->philo_has_died || (option && !philo->philo_is_full))
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->next->left_fork);
		mutex_print(philo, "has taken a fork\n");
		mutex_print(philo, "has taken a fork\n");
		mutex_print(philo, "is eating\n");
		usleep(time * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->next->left_fork);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	philo->last_meal_time = get_current_time();
	if (option)
	{
		philo->total_meals_eaten++;
		if (philo->total_meals_eaten == philo->data->max_nb_of_meals)
			philo->philo_is_full = TRUE;
	}
}

void    philo_is_sleeping(t_philo *philo)
{
	int     time;
	int		option;

	time = philo->data->time_to_sleep;
	option = philo->data->max_meal_option;
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (!philo->data->philo_has_died || (option && !philo->philo_is_full))
	{
		mutex_print(philo, "is sleeping\n");
		usleep(time * 1000);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
}

void	philo_is_thinking(t_philo *philo)
{
	int		option;

	option = philo->data->max_meal_option;
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (!philo->data->philo_has_died || (option && !philo->philo_is_full))
		mutex_print(philo, "is thinking\n");
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
}



// printf("\n\nERROR\n\n\n");
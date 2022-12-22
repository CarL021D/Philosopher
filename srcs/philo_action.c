#include "philosopher.h"

<<<<<<< HEAD
// TODO

=======
void    set_philo_state(t_philo *node, int state)
{
	node->philo_is_eating = FALSE;
	node->philo_is_sleeping = FALSE;
	node->philo_is_thinking = FALSE;
	if (state == EATING)
		node->philo_is_eating = TRUE;
	else if (state == SLEEPING)
		node->philo_is_sleeping = TRUE;
	else if (state == THINKING)
		node->philo_is_thinking = TRUE;
}

int    nxt_philo_has_left_fork(t_data *data, t_philo **philo, t_philo *node)
{
	if (node->index == (data->nb_of_philos - 1) \
	&& (*philo)->left_fork == TRUE)
		return (TRUE);
	else if (node->next->left_fork == TRUE)
		return (TRUE);
	return (FALSE);
}

void    drop_fork(t_philo **philo, t_philo *node)
{
	node->right_fork = FALSE;
	if (node->next != NULL)
		node->next->left_fork = TRUE;
	else
		(*philo)->left_fork = TRUE;
}
>>>>>>> 209f6e4fb3383986e2c510f00e4eee8a83b7d913

void	mutex_print(t_philo *philo, char *message)
{
<<<<<<< HEAD
	long	current_time;

	pthread_mutex_lock(&philo->data->lock_print);
	current_time = get_current_time() - philo->data->launch_time;
	printf("%ld - %d %s\n", current_time, philo->index, message);
	pthread_mutex_unlock(&philo->data->lock_print);
}

int		philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		philo->data->philo_has_died = TRUE;
		mutex_print(philo, "died\n");

	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
=======
	if (node->left_fork == TRUE \
	&& nxt_philo_has_left_fork(data, philo, node) == TRUE)
	{
		node->right_fork = TRUE;
		if (node->next != NULL)
			node->next->left_fork = FALSE;
		else
			(*philo)->left_fork = FALSE;
	}
}

void    philo_is_dead(t_data *data, t_philo **philo, t_philo *node)
{
	if (node->philo_is_thinking)
	{

		data->philo_has_died = TRUE;
	}
}
>>>>>>> 209f6e4fb3383986e2c510f00e4eee8a83b7d913

}

void    philo_is_eating(t_philo *philo)
{
	int     time;
<<<<<<< HEAD

	time = philo->data->time_to_eat;
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == FALSE)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->next->left_fork);

		mutex_print(philo, "has lock a fork\n");
		mutex_print(philo, "has lock a fork\n");
		mutex_print(philo, "is eating\n");
		usleep(time * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->next->left_fork);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	philo->last_meal_time = get_current_time();
	philo->total_meals_eaten++;
=======

	time = data->time_to_eat;
	if (data->philo_has_died == FALSE)
	{
		take_fork(data, philo, node);
		printf("%d is eating\n", node->index);
		usleep(time);
		set_philo_state(node, EATING);
		drop_fork(philo, node);
	}
>>>>>>> 209f6e4fb3383986e2c510f00e4eee8a83b7d913
}

void    philo_is_sleeping(t_philo *philo)
{
<<<<<<< HEAD
	int     time;

	time = philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == FALSE)
	{
		mutex_print(philo, "is sleeping\n");
		usleep(time);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
=======
	int time;

	time = data->time_to_sleep;
	if (data->philo_has_died == FALSE && node->philo_is_eating == TRUE)
	{
		printf("%d is sleeping\n", node->index);
		usleep(time);
		set_philo_state(node, SLEEPING);
	}
>>>>>>> 209f6e4fb3383986e2c510f00e4eee8a83b7d913
}

void	philo_is_thinking(t_philo *philo)
{
<<<<<<< HEAD
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == FALSE)
		mutex_print(philo, "is thinking\n");
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
=======
	if (data->philo_has_died == FALSE)
	{
		printf("%d is thinking\n", node->index);
		set_philo_state(node, THINKING);
	}
>>>>>>> 209f6e4fb3383986e2c510f00e4eee8a83b7d913
}

#include "philosopher.h"

t_philo	*create_node(void)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

int		create_linked_list(t_data *data, t_philo **philo_lst)
{
	t_philo		*philo;
	int			i;

	i = 1;
	philo = create_node();
	if (!philo)
		return (ERROR);
	*philo_lst = philo;
	while (i < data->nb_of_philos)
	{
		philo = *philo_lst;
		while (philo->next)
			philo = philo->next;
		philo->next = create_node();
		if (!philo)
			return (ERROR);
		i++;
	}
	return (1);
}

void	free_circular_linked_list(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		*philo_lst = (*philo_lst)->next;
		free(philo);
		i++;
		philo = *philo_lst;
	}
}

int		destroy_threads(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (!pthread_join(philo->thread, NULL))
			return (ERROR);
		i++;
		philo = philo->next;
	}
	return (0);
}

void	destroy_mutex(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	pthread_mutex_destroy(&data->philo_has_died_mutex);
	pthread_mutex_destroy(&data->max_nb_of_meals_mutex);
	pthread_mutex_destroy(&data->lock_print);
	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&philo->left_fork);
		pthread_mutex_destroy(&philo->last_meal_time_mutex);
		philo = philo->next;
		i++;
	}
}

void	init_mutex(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	pthread_mutex_init(&data->philo_has_died_mutex, NULL);
	pthread_mutex_init(&data->max_nb_of_meals_mutex, NULL);
	pthread_mutex_init(&data->lock_print, NULL);
	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_init(&philo->left_fork, NULL);
		pthread_mutex_init(&philo->last_meal_time_mutex, NULL);
		philo = philo->next;
		i++;
	}
}

static void     init_philo_struct(t_philo **philo_lst, t_data *data)
{
	t_philo     *philo;
	int         i;

	philo = (*philo_lst);
	i = 1;
	while (i <= data->nb_of_philos)
	{
		philo->index = i;
		philo->philo_is_sleeping = FALSE;
		philo->philo_is_thinking = FALSE;
		philo->last_meal_time = 0;
		philo->total_meals_eaten = 0;
		philo->data = data;
		if (data->nb_of_philos > 1 && i == data->nb_of_philos)
			philo->next = *philo_lst;
		else
			philo = philo->next;
		i++;
	}
}

static int  init_struct(t_data *data, int ac, char **av)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->philo_has_died = FALSE;
	data->max_meal_option = FALSE;
	if (ac == 6)
	{
		data->max_nb_of_meals = ft_atoi(av[5]);
		data->max_meal_option = TRUE;
		data->every_philo_full = FALSE;
	}
	// data->philos = malloc(sizeof(pthread_t) * data->nb_of_philos);
	// if (!data->philos)
	// 	return (ERROR);
	return (1);
}

int    init_data(t_philo **philo_lst, t_data *data, int ac, char **av)
{
	if (init_struct(data, ac, av) == ERROR)
		return (ERROR);
	create_linked_list(data, philo_lst);	
	if (create_linked_list(data, philo_lst) == ERROR)
	{
		// free(data->philos);
		free_list(philo_lst);
		return (ERROR);
	}
	init_philo_struct(philo_lst, data);
	init_mutex(philo_lst, data);
	return (1);
}

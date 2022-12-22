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

static int  create_list(t_data *data, t_philo **lst_philo)
{
	t_philo		*philo;
	int			i;

	i = 1;
	philo = create_node();
	if (!philo)
		return (ERROR);
	*lst_philo = philo;
	while (i < data->nb_of_philos)
	{
		philo = *lst_philo;
		while (philo->next)
			philo = philo->next;
		philo->next = create_node();
		if (!philo)
			return (ERROR);
		i++;
	}
	// if (data->nb_of_philos > 1)
	// {
	// 	philo = philo->next;
	// 	philo->next = *lst_philo;
	// }
	return (1);
}

static void     init_t_philo(t_data *data, t_philo **lst_philo)
{
	t_philo     *philo;
	int         i;

	philo = (*lst_philo);
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
			philo->next = *lst_philo;
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
	if (ac == 6)
		data->max_nb_of_meals = ft_atoi(av[5]);
	data->philos = malloc(sizeof(pthread_t) * data->nb_of_philos);
	if (!data->philos)
		return (ERROR);
	return (1);
}

int    init_data(t_data *data, t_philo **lst_philo, int ac, char **av)
{
	if (init_struct(data, ac, av) == ERROR)
		return (ERROR);
	create_list(data, lst_philo);	
	if (create_list(data, lst_philo) == ERROR)
	{
		free(data->philos);
		free_list(lst_philo);
		return (ERROR);
	}

	init_t_philo(data, lst_philo);
	return (1);
}
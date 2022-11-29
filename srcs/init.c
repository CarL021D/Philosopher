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

static int  create_list(t_data *data, t_philo **philo)
{
	t_philo		*node;
	int			i;

	i = 1;
	node = create_node();
    if (!node)
        return (ERROR);
	*philo = node;
	while (i < data->nb_of_philos)
	{
		node = *philo;
		while (node->next)
			node = node->next;
		node->next = create_node();
        if (!node)
            return (ERROR);
		i++;
	}
    return (1);
}

static void     init_list(t_data *data, t_philo **philo)
{
    t_philo     *node;
    int         i;

    node = *philo;
    i = 0;
    while (i < data->nb_of_philos)
    {
        node->left_fork = TRUE;
        node->right_fork = FALSE;
        node->total_meals_eaten = 0;
        node->is_dead = FALSE;
        node = node->next;
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

int    init_data(t_data *data, t_philo **philo, int ac, char **av)
{
    if (init_struct(data, ac, av) == ERROR)
        return (ERROR);
    if (create_list(data, philo) == ERROR)
    {
        free(data->philos);
        free_list(philo);
        return (ERROR);
    }
    init_list(data, philo);
    return (1);
}
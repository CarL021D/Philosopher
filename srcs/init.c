#include "philosopher.h"

int init_struct(t_data *s_data, int ac, char **av)
{
    s_data->nb_of_philos = ft_atoi(av[1]);
    s_data->time_to_die = ft_atoi(av[2]);
    s_data->time_to_eat = ft_atoi(av[3]);
    s_data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        s_data->max_nb_of_meals = ft_atoi(av[5]);
    s_data->philos = malloc(sizeof(pthread_t) * s_data->nb_of_philos);
    if (!s_data->philos)
        return (ERROR);
    return (1);
}
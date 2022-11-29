#include "philosopher.h"

int main(int ac, char **av)
{
    t_data      data;
    t_philo     *philo;

    if (exit_if_args_errors(ac, av) == ERROR)
        return (1);
    if (init_data(&data, &philo, ac, av) == ERROR)
        return (1);
}
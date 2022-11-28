#include "philosopher.h"

static int nb_of_args_check(int ac)
{
    if (ac < 5 || ac > 6)
    {
        write(2, "Error, uncorrect number of arguments\n", 37);
        return (1);
    }
    return (0);
}

static int args_are_num_check(char **av)
{
    int     i;
    int     j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
            {
                write(2, "Error, some characters are not numbers\n", 39);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static int    exit_if_params_errors(int ac, char **av)
{
    if (ft_atoi(av[1]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
    {
        write(2, "Error, param value must be greater than zero\n", 45);
        return (1);
    }
    return (0);
}

static int args_out_of_range_check(char **av)
{
    long long       nb;
    int             i;

    i = 1;
    while (av[i])
    {
        nb = ft_atoi(av[i]);
        if (nb < 0 || nb > INT_MAX)
        {
            write(2, "Error, element out of range value\n", 34);
            return (1);
        }
        i++;
    }
    return (0);
}

int exit_if_args_errors(int ac, char **av)
{
    if (nb_of_args_check(ac))
        return (1);
    else if (args_are_num_check(av))
        return (1);
    else if (exit_if_params_errors(ac, av))
        return (1);
    else if (args_out_of_range_check(av))
        return (1);
    return (0);
}

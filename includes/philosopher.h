#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_data
{
    int     nb_of_philos;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     has_died;
    int     max_nb_of_meals;
}   t_data;


//                  ERROR HANDLING
int     exit_if_args_errors(int ac, char **av);

//                  UTILS
int	ft_atoi(const char *nptr);


#endif
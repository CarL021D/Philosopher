#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

# define FALSE 0
# define TRUE 1 
# define ERROR 2 

typedef struct s_data
{
    pthread_t   *philos;
    int         nb_of_philos;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         has_died;
    int         max_nb_of_meals;
}   t_data;

typedef struct s_philo
{
    int             left_fork;
    int             right_fork;
    int             total_meals_eaten;
    int             is_dead;
    struct s_philo  *next;
}   t_philo;

//                  INIT
int    init_data(t_data *data, t_philo **philo, int ac, char **av);

//                  ERROR HANDLING
int exit_if_args_errors(int ac, char **av);

//                  FREE
void	free_list(t_philo **philo);

//                  UTILS
int	ft_atoi(const char *nptr);


#endif
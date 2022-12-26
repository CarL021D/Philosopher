#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1 
# define ERROR 2

typedef struct s_data
{
	pthread_mutex_t		philo_has_died_mutex;
	pthread_mutex_t		max_nb_of_meals_mutex;
	pthread_mutex_t		lock_print;
	int					nb_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_has_died;
	int					max_meal_option;
	int					max_nb_of_meals;
	int					every_philo_full;
	long				launch_time;
}   t_data;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t	    left_fork;
	pthread_mutex_t		last_meal_time_mutex;
	int					index;
	int				    philo_is_sleeping;
	int				    philo_is_thinking;
	int				    total_meals_eaten;
	long				last_meal_time;
	struct s_data		*data;
	struct s_philo		*next;
}   t_philo;

//				INIT
int    init_data(t_philo **philo, t_data *data, int ac, char **av);

//				PHILO
long    get_current_time(void);
void    philo_is_eating(t_philo *philo);
void    philo_is_sleeping(t_philo *node);
void	philo_is_thinking(t_philo *node);
void	mutex_print(t_philo *philo, char *message);

//				LINKED LIST
t_philo	*create_node(void);
int		create_linked_list(t_data *data, t_philo **philo_lst);
void	free_list(t_philo **philo);
void	free_circular_linked_list(t_philo **philo_lst, t_data *data);


//				THREAD
int		destroy_threads(t_philo **philo_lst, t_data *data);

//				MUTEX
void	init_mutex(t_philo **philo_lst, t_data *data);
void	destroy_mutex(t_philo **philo_lst, t_data *data);

//				ERROR HANDLING
int exit_if_args_errors(int ac, char **av);

//				UTILS
int	ft_atoi(const char *nptr);

#endif
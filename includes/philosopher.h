/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:20:28 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/30 17:27:58 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define ERROR 2

typedef struct s_data
{
	pthread_mutex_t		philo_has_died_mutex;
	pthread_mutex_t		every_philo_full_mutex;
	pthread_mutex_t		max_meal_option_mutex;
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
	int					philo_is_sleeping;
	int					philo_is_thinking;
	int					philo_is_full;
	int					total_meals_eaten;
	long				last_meal_time;
	struct s_data		*data;
	struct s_philo		*next;
}   t_philo;

//				INIT
int		init_data(t_philo **philo, t_data *data, int ac, char **av);

//				PHILO
void	desync_action_for_even_philo_count(t_philo *philo);
void	desync_action_for_odd_philo_count(t_philo *philo);
void	philo_is_eating(t_philo *philo);
void	philo_is_sleeping(t_philo *node);
void	philo_is_thinking(t_philo *node);
void	mutex_print(t_philo *philo, char *message);
int		all_philo_full(t_philo *philo);
int		philo_died(t_philo *philo);
int		kill_philo_if_possible(t_philo *philo);

//				LINKED LIST
t_philo	*create_node(void);
int		create_linked_list(t_data *data, t_philo **philo_lst);
void	free_list(t_philo **philo);
void	free_circular_linked_list(t_philo **philo_lst, t_data *data);


//				THREAD
void	philo_routine(t_philo *philo);
void	launch_philo_routine(t_philo **philo_lst, t_data *data);
void	stop_routine_if_philo_dead_or_full(t_philo **philo_lst, t_data *data);
int		try_to_set_all_philo_to_full(t_philo *philo, t_data *data);
int		destroy_threads(t_philo **philo_lst, t_data *data);

//				MUTEX
void	init_mutex(t_philo **philo_lst, t_data *data);
void	destroy_mutex(t_philo **philo_lst, t_data *data);

//				ERROR HANDLING
int		exit_if_args_errors(int ac, char **av);

//				UTILS
long	get_current_time(void);
int		ft_atoi(const char *nptr);

#endif
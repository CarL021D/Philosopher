#include "philosopher.h"

void    set_philo_state(t_philo *node, int state)
{
    node->philo_is_eating = FALSE;
    node->philo_is_sleeping = FALSE;
    node->philo_is_thinking = FALSE;
    if (state == EATING)
        node->philo_is_eating = TRUE;
    else if (state == SLEEPING)
        node->philo_is_sleeping = TRUE;
    else if (state == THINKING)
        node->philo_is_thinking = TRUE;
}

int    nxt_philo_has_left_fork(t_data *data, t_philo **philo, t_philo *node)
{
    if (noode->index == (data->nb_of_philos - 1) \
    && (*philo)->left_fork == TRUE)
        return (TRUE);
    else if (node->next->left_fork == TRUE)
        return (TRUE);
    return (FALSE);
}

void    drop_fork(t_philo **philo, t_philo *node)
{
    node->right_fork = FALSE;
    if (node->next != NULL)
        node->next->left_fork = TRUE;
    else
        (*philo)->left_fork == TRUE;
}

void    take_fork(t_data *data, t_philo **philo, t_philo *node)
{
    int         i;

    if (node->left_fork == TRUE \
    && nxt_philo_has_left_fork(data, philo, node) == TRUE)
    {
        node->right_fork = TRUE;
        if (node->next != NULL)
            node->next->left_fork == FALSE;
        else
            (*philo)->left_fork == FALSE;
    }
}

// TODO
void    philo_is_dead(t_data *data, t_philo **philo, t_philo *node)
{
    if (node->philo_is_thinking)
    {

    }
}


void    philo_is_eating(t_data *data, t_philo **philo, t_philo *node)
{
    int     time;

    time = data->time_to_eat;
    if (data->philo_has_died == FALSE)
    {
        take_fork(data, philo, node);
        printf("%d is eating\n", node->index);
        usleep(data->time_to_eat);
        set_philo_state(node, EATING);
        drop_fork(philo, node);
    }
}

void    philo_is_sleeping(t_data *data, t_philo *node)
{
    int     time;

    time = data->time_to_sleep;
    if (data->philo_has_died == FALSE)
    {
        printf("%d is sleeping\n", node->index);
        usleep(time);
        set_philo_state(SLEEPING);
    }
}

void    philo_is_thinking(t_data *data, t_philo *node)
{
    if (data->philo_has_died == FALSE)
    {
        printf("%d is thinking\n", node->index);
        set_philo_state(node, THINKING);
    }
}

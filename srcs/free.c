#include "philosopher.h"

void	free_list(t_philo **philo)
{
    t_philo		*node;

	while (*philo)
	{
		node = (*philo)->next;
		free(*philo);
		*philo = node;
	}
}

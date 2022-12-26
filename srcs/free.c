/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:20:09 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/26 18:20:11 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

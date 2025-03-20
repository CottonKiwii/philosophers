/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/20 17:54:11 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int		start_routine(t_philo *philo)
{
	if (pthread_mutex_lock(philo->data->lock))
		return (FLS);
	if (philo->data->start)
		return (TR);
	return (FLS);
}

static int	wait_for_start(t_philo *philo)
{
	if (philo->idx + 1 == philo->data->philo_amount)
		philo->data->start = 1;
	while (start_routine(philo))
	{
		if (pthread_mutex_unlock(philo->data->lock))
			return (FLS);
	}
	if (pthread_mutex_unlock(philo->data->lock))
		return (FLS);
	return (TR);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	while (philo->data->end_program)
	{}
	return (NULL);
}

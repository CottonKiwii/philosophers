/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/21 13:00:06 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int		start_routine(t_philo *philo)
{
	unsigned int	res;

	if (pthread_mutex_lock(philo->data->lock))
		return (FLS);
	res = philo->data->start;
	if (pthread_mutex_unlock(philo->data->lock))
		return (FLS);
	return (res);
	/*if (philo->data->start)
		return (TR);
	return (FLS);*/
}

static int	wait_for_start(t_philo *philo)
{
	while (!start_routine(philo))
		;
	return (TR);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	printf("%lu %u is starting routine\n", gettime(philo->data->start), philo->idx); // dev
	while (philo->data->end_program)
	{}
	return (NULL);
}

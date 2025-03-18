/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/18 13:13:47 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (pthread_mutex_lock(philo->lock))
		return (NULL);
	if (pthread_mutex_unlock(philo->lock))
		return (NULL);
	philo->start = gettime(0);
	if (check_death(NULL, philo))
		return (NULL);
	while (philo->time->end_program)
	{}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/28 16:06:44 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_start(t_philo *philo)
{
	unsigned int	res;

	while (1)
	{
		pthread_mutex_lock(philo->data->lock);
		res = philo->data->start;
		if (res)
			break ;
		pthread_mutex_unlock(philo->data->lock);
		usleep(100);
	}
	philo->start = philo->data->start;
	pthread_mutex_unlock(philo->data->lock);
		
	return (TR);
}

void	*lonely_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_for_end(philo->data))
	{
		ft_sleep(philo->data, 1);
		pthread_mutex_lock(philo->fork);
		print_fork(philo, philo->idx + 1);
		ft_sleep(philo->data, philo->to_die);
	}
	pthread_mutex_unlock(philo->fork);
	return (NULL);
}

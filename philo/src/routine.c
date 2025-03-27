/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/27 16:19:29 by jwolfram         ###   ########.fr       */
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
}

int	wait_for_start(t_philo *philo)
{
	while (!start_routine(philo))
		;
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
		put_msg(FORK, philo, philo->data, philo->idx + 1);
		ft_sleep(philo->data, philo->to_die);
	}
	return (NULL);
}

int	put_msg(t_msg status, t_philo *philo, t_data *data, unsigned int idx)
{
	pthread_mutex_lock(data->lock);
	if (philo && !philo->start)
		philo->start = data->start;
	if (status == DEATH)
		printf("%lu %u died\n", gettime(data->start), idx);
	if (!data->end_program)
	{
		pthread_mutex_unlock(data->lock);
		return (FLS);
	}
	if (status == FORK)
		printf("%lu %u has taken a fork\n", gettime(philo->start), idx);
	else if (status == EAT)
		printf("%lu %u is eating\n", gettime(philo->start), idx);
	else if (status == SLEEP)
		printf("%lu %u is sleeping\n", gettime(philo->start), idx);
	else if (status == THINK)
		printf("%lu %u is thinking\n", gettime(philo->start), idx);
	pthread_mutex_unlock(data->lock);
	return (TR);
}

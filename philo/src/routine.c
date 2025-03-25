/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/25 13:57:25 by jwolfram         ###   ########.fr       */
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
		if (put_msg(FORK, philo, philo->data, philo->idx + 1))
			return (NULL);
		ft_sleep(philo->data, philo->to_die);
	}
	return (NULL);
}

int	put_msg(t_msg status, t_philo *philo, t_data *data, unsigned int idx)
{
	int				check;

	pthread_mutex_lock(data->lock);
	check = 0;
	if (philo && !philo->start)
		philo->start = data->start;
	if (status == DEATH)
		check = printf("%lu %u died\n", gettime(data->start), idx);
	if (check == -1)
		return (pthread_mutex_unlock(data->lock), FLS);
	if (!data->end_program)
		return (pthread_mutex_unlock(data->lock), TR);
	if (status == FORK)
		check = printf("%lu %u has taken a fork\n", gettime(philo->start), idx);
	else if (status == EAT)
		check = printf("%lu %u is eating\n", gettime(philo->start), idx);
	else if (status == SLEEP)
		check = printf("%lu %u is sleeping\n", gettime(philo->start), idx);
	else if (status == THINK)
		check = printf("%lu %u is thinking\n", gettime(philo->start), idx);
	pthread_mutex_unlock(data->lock);
	if (check == -1)
		return (FLS);
	return (TR);
}

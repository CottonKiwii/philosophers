/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/24 18:04:21 by jwolfram         ###   ########.fr       */
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

static int	wait_for_start(t_philo *philo)
{
	while (!start_routine(philo))
		;
	return (TR);
}

static int	check_for_end(t_data *data)
{
	unsigned int	res;

	pthread_mutex_lock(data->lock);
	res = data->end_program;	
	pthread_mutex_unlock(data->lock);
	return (res);
}

void	even_routine(t_philo *philo)
{
	ft_sleep(philo->data, 1);
	pthread_mutex_lock(philo->fork);
	if (put_msg(FORK, philo, philo->data, philo->idx + 1))
		return ;
	pthread_mutex_lock(philo->next->fork);
	if (put_msg(FORK, philo, philo->data, philo->idx + 1))
		return ;
	if (put_msg(EAT, philo, philo->data, philo->idx + 1))
		return ;
	update_time(philo);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	ft_sleep(philo->data, philo->data->to_eat);
	if (put_msg(SLEEP, philo, philo->data, philo->idx + 1))
		return ;
	ft_sleep(philo->data, philo->data->to_sleep);
	if (put_msg(THINK, philo, philo->data, philo->idx + 1))
		return ;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	printf("%lu %u is starting routine\n", gettime(philo->data->start), philo->idx + 1); // dev
	gettime(philo->start);
	while (check_for_end(philo->data))
	{
		if (philo->idx % 2)
			even_routine(philo);				
		//else
			// even number routine here
	}
	return (NULL);
}

int	routine_init(t_data *data)
{
	t_philo			*philo;

	data->lock = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->lock)
		return (FLS);
	philo = data->philo_first;
	if (pthread_mutex_init(data->lock, NULL))
		return (FLS);
	if (pthread_mutex_lock(data->lock))
		return (FLS);
	if (pthread_init(philo))
		return (FLS);
	data->start = gettime(0);
	if (pthread_mutex_unlock(data->lock))
		return (FLS);
	if (check_loop(data))
		return (FLS);
	return (TR);
}

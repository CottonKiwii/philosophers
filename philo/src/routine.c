/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:23 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/21 17:27:48 by jwolfram         ###   ########.fr       */
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
	put_msg(FORK, philo->data, philo->idx + 1);
	pthread_mutex_lock(philo->next->fork);
	put_msg(FORK, philo->data, philo->idx + 1);
	put_msg(EAT, philo->data, philo->idx + 1);
	printf("die time before %lu\n", philo->data->check[philo->idx]);
	update_time(philo);
	printf("die time after %lu\n", philo->data->check[philo->idx]);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	ft_sleep(philo->data, philo->data->to_eat);
	put_msg(SLEEP, philo->data, philo->idx + 1);
	ft_sleep(philo->data, philo->data->to_sleep);
	put_msg(THINK, philo->data, philo->idx + 1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	printf("%lu %u is starting routine\n", gettime(philo->data->start), philo->idx); // dev
	while (check_for_end(philo->data))
	{
		if (philo->idx % 2)
			even_routine(philo);				
		//else
			// even number routine here
	}
	return (NULL);
}

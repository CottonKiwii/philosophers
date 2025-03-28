/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/28 17:17:47 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettime(unsigned long start)
{
	struct timeval	cur;
	unsigned long	time;

	gettimeofday(&cur, NULL);
	time = cur.tv_sec * 1000 + (cur.tv_usec / 1000);
	return (time - start);
}

unsigned long	getmicrosec(unsigned long start)
{
	struct timeval	cur;
	unsigned long	time;

	gettimeofday(&cur, NULL);
	time = cur.tv_usec + (cur.tv_sec * 1000000);
	return (time - start);
}

void	update_time(t_philo *philo)
{
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	pthread_mutex_lock(philo->data->lock);
	philo->data->check[philo->idx] = gettime(0);
	pthread_mutex_unlock(philo->data->lock);
}

int	check_eat_amount(t_data *data)
{
	pthread_mutex_lock(data->lock);
	data->philos_full++;
	if (data->philos_full == data->philo_amount)
	{
		data->end_program = TR;
		return (pthread_mutex_unlock(data->lock), FLS);
	}
	pthread_mutex_unlock(data->lock);
	return (TR);
}

int	check_loop(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(data->lock);
		data->check[i] = data->start;
		pthread_mutex_unlock(data->lock);
		i++;
	}
	while (check_for_end(data))
	{
		i = 0;
		while (i < data->philo_amount) 
		{
			pthread_mutex_lock(data->lock);
			if (gettime(data->check[i]) >= data->to_die)
			{
				print_death(data, i + 1);
				pthread_mutex_unlock(data->lock);
				return (TR);
			}
			pthread_mutex_unlock(data->lock);
			i++;
		}
		usleep(100);
	}
	return (TR);
}

int	check_for_end(t_data *data)
{
	unsigned int	res;

	pthread_mutex_lock(data->lock);
	res = data->end_program;	
	pthread_mutex_unlock(data->lock);
	return (res);
}

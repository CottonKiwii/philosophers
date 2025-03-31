/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:08:34 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/31 12:08:37 by jwolfram         ###   ########.fr       */
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

static int	check_death(t_data *data)
{
	unsigned int	i;

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
	return (FLS);
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
		if (!check_death(data))
			break ;
		usleep(100);
	}
	return (TR);
}

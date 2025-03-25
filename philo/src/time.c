/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/25 13:44:08 by jwolfram         ###   ########.fr       */
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

int	update_time(t_philo *philo)
{
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	if (pthread_mutex_lock(philo->data->lock))
		return (FLS);
	philo->data->check[philo->idx] = gettime(0);
	if (pthread_mutex_unlock(philo->data->lock))
		return (FLS);
	return (TR);
}

void	check_eat_amount(t_data *data)
{
	pthread_mutex_lock(data->lock);
	data->philos_full++;
	if (data->philos_full == data->philo_amount)
		data->end_program = TR;
	pthread_mutex_unlock(data->lock);
}

int	check_loop(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		data->check[i] = data->start;
		i++;
	}
	while (data->end_program)
	{
		i = 0;
		while (i < data->philo_amount) 
		{
			if (gettime(data->check[i]) >= data->to_die)
			{
				data->end_program = TR;
				put_msg(DEATH, NULL, data, i + 1);
				break ;
			}
			i++;
		}
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

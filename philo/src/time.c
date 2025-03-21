/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/21 14:51:36 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_time(t_philo *philo)
{
	if (pthread_mutex_lock(philo->data->lock))
		return (FLS);
	philo->data->check[philo->idx] = gettime(philo->data->start);
	if (pthread_mutex_unlock(philo->data->lock))
		return (FLS);
	return (TR);
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
		if (check_time(data))
			return (FLS);
	}
	return (TR);
}

int	put_msg(t_msg status, t_data *data, int idx)
{
	int				check;

	pthread_mutex_lock(data->lock);
	check = 0;
	if (status == DEATH)
		check = printf("%lu %u died\n", gettime(data->start), idx);
	if (check == -1)
		return (pthread_mutex_unlock(data->lock), FLS);
	if (!data->end_program)
		return (pthread_mutex_unlock(data->lock), TR);
	if (status == FORK)
		check = printf("%lu %u has taken a fork\n", gettime(data->start), idx);
	else if (status == EAT)
		check = printf("%lu %u is eating\n", gettime(data->start), idx);
	else if (status == SLEEP)
		check = printf("%lu %u is sleeping\n", gettime(data->start), idx);
	else if (status == THINK)
		check = printf("%lu %u is thinking\n", gettime(data->start), idx);
	pthread_mutex_unlock(data->lock);
	if (check == -1)
		return (FLS);
	return (TR);
}

int	check_time(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_amount) 
	{
		if (gettime(data->check[i]) >= data->to_die)
		{
			data->end_program = TR;
			put_msg(DEATH, data, i + 1);
			break ;
		}
		i++;
	}
	return (TR);
}

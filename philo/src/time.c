/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/21 13:19:32 by jwolfram         ###   ########.fr       */
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

	check = 0;
	if (status == DEATH)
		check = printf("%lu %u died\n", gettime(data->start), idx);
	if (check == -1)
		return (FLS);
	if (!data->end_program)
		return (TR);
	if (status == FORK)
		check = printf("%lu %u has taken a fork\n", gettime(data->start), idx);
	else if (status == EAT)
		check = printf("%lu %u is eating\n", gettime(data->start), idx);
	else if (status == SLEEP)
		check = printf("%lu %u is sleeping\n", gettime(data->start), idx);
	else if (status == THINK)
		check = printf("%lu %u is thinking\n", gettime(data->start), idx);
	if (check == -1)
		return (FLS);
	return (TR);
}

int	check_time(t_data *data)
{
	unsigned int	i;
	//static int counter = 0;

	if (pthread_mutex_lock(data->lock))
		return (FLS);
	i = 0;
	while (i < data->philo_amount) 
	{
		//printf("are we here? %d\n", counter++);
		if (gettime(data->check[i]) >= data->to_die)
		{
			data->end_program = TR;
			//printf("hello\n");
			put_msg(DEATH, data, i + 1);
			break ;
		}
		i++;
	}
	//printf("here?\n");
	if (pthread_mutex_unlock(data->lock))
		return (FLS);
	return (TR);
}

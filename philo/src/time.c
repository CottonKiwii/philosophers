/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/20 17:11:56 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_time(t_philo *philo)
{
	if (pthread_mutex_lock(philo->data->lock))
		return (FLS);
	if (!philo->start)
		philo->start = gettime(0);
	philo->data->check[philo->idx] = gettime(philo->start);
	if (pthread_mutex_unlock(philo->data->lock))
		return (FLS);
	return (TR);
}

int	check_loop(t_data *data)
{
	while (data->end_program)
	{
		if (check_time(data))
			return (FLS);
	}
	return (TR);
}

int	put_msg(t_msg status, t_philo *philo)
{
	int				check;

	check = 0;
	if (status == DEATH)
		check = printf("%lu %u died\n", gettime(philo->start), philo->idx);
	if (check == -1)
		return (FLS);
	if (!philo->data->end_program)
		return (TR);
	if (status == FORK)
		check = printf("%lu %u has taken a fork\n", gettime(philo->start), philo->idx);
	else if (status == EAT)
		check = printf("%lu %u is eating\n", gettime(philo->start), philo->idx);
	else if (status == SLEEP)
		check = printf("%lu %u is sleeping\n", gettime(philo->start), philo->idx);
	else if (status == THINK)
		check = printf("%lu %u is thinking\n", gettime(philo->start), philo->idx);
	if (check == -1)
		return (FLS);
	return (TR);
}

int	check_time(t_data *data)
{
	unsigned int	i;

	if (pthread_mutex_lock(data->lock))
		return (FLS);
	i = 0;
	while (i < data->philo_amount) 
	{
		if (gettime(data->check[i]) >= data->to_die)
		{
			data->end_program = TR;
			put_msg(DEATH, get_philo(data, i + 1));
			break ;
		}
		i++;
	}
	if (pthread_mutex_unlock(data->lock))
		return (FLS);
	return (TR);
}

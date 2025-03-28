/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:31:26 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/28 16:37:39 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_data *data, unsigned int idx)
{
	data->end_program = TR;
	printf("%lu %u died\n", gettime(data->start), idx);
	return ;
}

int	print_fork(t_philo *philo, unsigned int idx)
{
	pthread_mutex_lock(philo->data->lock);
	if (!philo->data->end_program)
	{
		pthread_mutex_unlock(philo->data->lock);
		return (FLS);
	}
	printf("%lu %u has taken a fork\n", gettime(philo->start), idx);
	pthread_mutex_unlock(philo->data->lock);
	return (TR);
}

int	print_eating(t_philo *philo, unsigned int idx)
{
	pthread_mutex_lock(philo->data->lock);
	if (!philo->data->end_program)
	{
		pthread_mutex_unlock(philo->data->lock);
		return (FLS);
	}
	printf("%lu %u is eating\n", gettime(philo->start), idx);
	pthread_mutex_unlock(philo->data->lock);
	return (TR);
}

int	print_sleeping(t_philo *philo, unsigned int idx)
{
	pthread_mutex_lock(philo->data->lock);
	if (!philo->data->end_program)
	{
		pthread_mutex_unlock(philo->data->lock);
		return (FLS);
	}
	printf("%lu %u is sleeping\n", gettime(philo->start), idx);
	pthread_mutex_unlock(philo->data->lock);
	return (TR);
}

int	print_thinking(t_philo *philo, unsigned int idx)
{
	pthread_mutex_lock(philo->data->lock);
	if (!philo->data->end_program)
	{
		pthread_mutex_unlock(philo->data->lock);
		return (FLS);
	}
	printf("%lu %u is thinking\n", gettime(philo->start), idx);
	pthread_mutex_unlock(philo->data->lock);
	return (TR);
}

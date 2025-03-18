/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/18 13:02:51 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_loop(t_data *data)
{
	while (data->time->end_program)
	{
		if (check_death(data, NULL))
			return (FLS);
	}
	return (TR);
}

int	check_death(t_data *data, t_philo *philo)
{
	unsigned int	i;
	pthread_mutex_t	lock;

	if (pthread_mutex_init(&lock, NULL))
		return (FLS);
	if (pthread_mutex_lock(&lock))
		return (pthread_mutex_destroy(&lock), FLS);
	if (philo)
		philo->time->check[philo->nbr] = gettime(philo->start);
	else
	{
		i = 0;
		while (i != data->time->philo_amount) 
		{
			if (gettime(data->time->check[i]) >= data->time->to_die)
			{
				data->time->end_program = TR;
				put_msg(DEATH, get_philo(data, i + 1));
				break ;
			}
			i++;
		}
	}
	if (pthread_mutex_unlock(&lock))
		return (pthread_mutex_destroy(&lock), FLS);
	return (pthread_mutex_destroy(&lock), TR);
}

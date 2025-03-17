/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:07:55 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/17 13:34:35 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_time *time, t_philo *philo)
{
	unsigned int	i;
	pthread_mutex_t	lock;

	if (pthread_mutex_init(&lock, NULL))
		return (FLS);
	if (pthread_mutex_lock(&lock))
		return (pthread_mutex_destroy(&lock), FLS);
	if (philo)
		time->check[philo->nbr] = gettime(philo->start);
	else
	{
		i = 0;
		while (i != time->philo_amount) 
		{
			if (gettime(time->check[i]) >= time->to_die)
			{
				time->end_program = TR;
				break ;
			}
			i++;
		}
	}
	if (pthread_mutex_unlock(&lock))
		return (pthread_mutex_destroy(&lock), FLS);
	return (pthread_mutex_destroy(&lock), TR);
}

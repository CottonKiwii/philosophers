/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/27 16:25:19 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	odd_philo_do(t_philo *philo)
{
	pthread_mutex_lock(philo->next->fork);
	if (put_msg(FORK, philo, philo->data, philo->idx + 1))
		return (pthread_mutex_unlock(philo->next->fork));
	pthread_mutex_lock(philo->fork);
	if (put_msg(FORK, philo, philo->data, philo->idx + 1))
		return (pthread_mutex_unlock(philo->next->fork), 
		pthread_mutex_unlock(philo->fork));
	if (put_msg(EAT, philo, philo->data, philo->idx + 1))
		return (pthread_mutex_unlock(philo->next->fork), 
		pthread_mutex_unlock(philo->fork));
	update_time(philo);
	if (!philo->eat_amount)
		check_eat_amount(philo->data);
	ft_sleep(philo->data, philo->to_eat);
	pthread_mutex_unlock(philo->next->fork);
	pthread_mutex_unlock(philo->fork);
	if (put_msg(SLEEP, philo, philo->data, philo->idx + 1))
		return (FLS);
	ft_sleep(philo->data, philo->to_sleep);
	if (put_msg(THINK, philo, philo->data, philo->idx + 1))
		return (FLS);
	ft_sleep(philo->data, philo->to_think);
	return (TR);
}

void	*odd_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	if (philo->philo_amount % 2 && philo->idx + 1 == philo->philo_amount)
		ft_sleep(philo->data, philo->to_eat * 2);
	while (check_for_end(philo->data))
		odd_philo_do(philo);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/28 16:49:23 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	odd_philo_do(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	if (print_fork(philo, philo->idx + 1))
		return (pthread_mutex_unlock(philo->fork));
	pthread_mutex_lock(philo->next->fork);
	if (print_fork(philo, philo->idx + 1))
		return (pthread_mutex_unlock(philo->next->fork), 
		pthread_mutex_unlock(philo->fork));
	update_time(philo);
	if (print_eating(philo, philo->idx + 1))
		return (pthread_mutex_unlock(philo->next->fork), 
		pthread_mutex_unlock(philo->fork));
	if (!philo->eat_amount)
		check_eat_amount(philo->data);
	ft_sleep(philo->data, philo->to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	if (print_sleeping(philo, philo->idx + 1))
		return (FLS);
	ft_sleep(philo->data, philo->to_sleep);
	if (print_thinking(philo, philo->idx + 1))
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

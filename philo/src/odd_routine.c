/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/26 17:32:25 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*odd_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	while (check_for_end(philo->data))
	{
		pthread_mutex_lock(philo->next->fork);
		if (put_msg(FORK, philo, philo->data, philo->idx + 1))
			return (NULL);
		pthread_mutex_lock(philo->fork);
		if (put_msg(FORK, philo, philo->data, philo->idx + 1))
			return (NULL);
		if (put_msg(EAT, philo, philo->data, philo->idx + 1))
			return (NULL);
		update_time(philo);
		if (!philo->eat_amount)
			check_eat_amount(philo->data);
		ft_sleep(philo->data, philo->to_eat);
		if (put_msg(SLEEP, philo, philo->data, philo->idx + 1))
			return (NULL);
		pthread_mutex_unlock(philo->next->fork);
		pthread_mutex_unlock(philo->fork);
		ft_sleep(philo->data, philo->to_sleep);
		if (put_msg(THINK, philo, philo->data, philo->idx + 1))
			return (NULL);
		ft_sleep(philo->data, philo->to_think);
	}
	return (NULL);
}

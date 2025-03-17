/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:33:45 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/17 14:51:26 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_init(t_data *data)
{
	t_time	*time;

	time = (t_time *)ft_calloc(1, sizeof(t_time));
	if (!time)
		return (FLS);
	time->philo_amount = ft_atoi(data->argv[1]);
	time->to_die = ft_atoi(data->argv[2]);
	time->to_eat = ft_atoi(data->argv[3]);
	time->to_sleep = ft_atoi(data->argv[4]);
	if (data->argv[5])
	time->eat_amount = ft_atoi(data->argv[5]);
	else
		time->eat_amount = 0;
	time->check = (unsigned long *)ft_calloc(ft_atoi(data->argv[1]), sizeof(unsigned int));
	if (!time->check)
		return (FLS);
	time->end_program = FLS;
	data->time = time;
	return (TR);
}

int	list_init(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 1;
	philo = NULL;
	while (i <= ft_atoi(data->argv[1]))
	{
		philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!philo)
			return (FLS);
		philo->nbr = i;
		philo->time = data->time;
		if (i == 1)
			data->philo_first = philo;
		else
			data->philo_last->next = philo;
		data->philo_last = philo;
		philo = philo->next;
		i++;
	}
	data->philo_last->next = data->philo_first;
	return (TR);
}

static int	pthread_init(t_philo *philo, pthread_mutex_t *lock)
{
	pthread_t		id;

	while (philo->nbr <= philo->time->philo_amount)
	{
		if (pthread_create(&id, NULL, philo_routine, (void *)philo))
			return (FLS);
		philo->id = id;
		philo->lock = lock;
		philo->fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		if (!philo->fork)
			return (FLS);
		if (pthread_mutex_init(philo->fork, NULL))
			return (FLS);
		printf("%d\n", philo->nbr);
		if (philo->nbr == philo->time->philo_amount)
			break ;
		philo = philo->next;
	}
	return (TR);
}

int	routine_init(t_data *data)
{
	t_philo			*philo;
	pthread_mutex_t	lock;

	philo = data->philo_first;
	if (pthread_mutex_init(&lock, NULL))
		return (FLS);
	if (pthread_mutex_lock(&lock))
		return (FLS);
	if (pthread_init(philo, &lock))
		return (FLS);
	if (pthread_mutex_unlock(&lock))
		return (FLS);
	while (1)
	{
		if (check_death(data->time, NULL))
			break ;
	}
	while (philo->nbr <= data->time->philo_amount)
	{
		if (pthread_join(philo->id, NULL))
			return (pthread_mutex_destroy(&lock), FLS);
		if (philo->nbr == philo->time->philo_amount)
			break ;
		philo = philo->next;
	}
	return (pthread_mutex_destroy(&lock), TR);
}

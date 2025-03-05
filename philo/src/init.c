/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:33:45 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/05 16:09:18 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_init(t_data *data)
{
	t_time	time;

	time.to_die = ft_atoi(data->argv[2]);
	time.to_eat = ft_atoi(data->argv[3]);
	time.to_sleep = ft_atoi(data->argv[4]);
	if (data->argv[5])
		time.eat_amount = ft_atoi(data->argv[5]);
	else
		time.eat_amount = 0;
	data->time = &time;
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
		philo->amount = ft_atoi(data->argv[1]);
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

static int	pthread_init(t_philo *philo, pthread_mutex_t lock)
{
	pthread_t		id;

	while (philo->nbr < philo->amount)
	{
		if (pthread_create(&id, NULL, philo_routine, (void *)philo))
			return (FLS);
		philo->id = id;
		if (pthread_mutex_init(&philo->fork, NULL))
			return (FLS);
		philo->lock = lock;		
		printf("%d\n", philo->nbr);
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
	if (pthread_init(philo, lock))
		return (FLS);
	if (pthread_mutex_unlock(&lock))
		return (FLS);
	while (philo->nbr < philo->amount)
	{
		if (pthread_join(philo->id, NULL))
			return (FLS);
		philo = philo->next;
	}
	pthread_mutex_destroy(&lock);
	return (TR);
}

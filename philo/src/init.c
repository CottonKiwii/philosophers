/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:33:45 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/31 11:54:18 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, char **argv)
{
	data->philo_amount = ft_atoi(argv[1]);
	data->to_die = ft_atoi(argv[2]);
	data->to_eat = ft_atoi(argv[3]);
	data->to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_amount = ft_atoi(argv[5]);
	else
		data->eat_amount = -1;
	data->check
		= (unsigned long *)ft_calloc(ft_atoi(argv[1]), sizeof(unsigned long));
	if (!data->check)
		return (FLS);
	data->end_program = FLS;
	return (TR);
}

int	list_init(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	philo = NULL;
	while (i < data->philo_amount)
	{
		philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!philo)
			return (FLS);
		philo->idx = i;
		philo->data = data;
		if (i == 0)
			data->philo_first = philo;
		else
			get_philo(data, i - 1)->next = philo;
		philo = philo->next;
		i++;
	}
	get_philo(data, data->philo_amount - 1)->next = data->philo_first;
	return (TR);
}

static void	pthread_set_values(t_philo *philo)
{
	philo->to_die = philo->data->to_die;
	philo->to_eat = philo->data->to_eat;
	philo->to_sleep = philo->data->to_sleep;
	philo->eat_amount = philo->data->eat_amount;
	philo->philo_amount = philo->data->philo_amount;
	if (philo->philo_amount % 2 && (philo->to_eat * 2) > philo->to_sleep)
		philo->to_think = philo->to_eat * 2 - philo->to_sleep;
	else if (!(philo->philo_amount % 2) && philo->to_eat > philo->to_sleep)
		philo->to_think = philo->to_eat - philo->to_sleep;
	else
		philo->to_think = 0;
}

int	pthread_init(t_philo *philo)
{
	while (philo->idx < philo->data->philo_amount)
	{
		philo->fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_set_values(philo);
		if (!philo->fork)
			return (FLS);
		if (pthread_mutex_init(philo->fork, NULL))
			return (FLS);
		if (philo->philo_amount == 1)
			pthread_create(&philo->id, NULL, lonely_routine, (void *)philo);
		else if (philo->idx % 2)
			pthread_create(&philo->id, NULL, even_routine, (void *)philo);
		else
			pthread_create(&philo->id, NULL, odd_routine, (void *)philo);
		if (philo->idx == philo->philo_amount - 1)
			break ;
		philo = philo->next;
	}
	return (TR);
}

int	routine_init(t_data *data)
{
	t_philo			*philo;

	data->lock = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->lock)
		return (FLS);
	philo = data->philo_first;
	if (pthread_mutex_init(data->lock, NULL))
		return (FLS);
	if (pthread_mutex_lock(data->lock))
		return (FLS);
	if (pthread_init(philo))
		return (FLS);
	data->start = gettime(0);
	if (pthread_mutex_unlock(data->lock))
		return (FLS);
	if (check_loop(data))
		return (FLS);
	return (TR);
}

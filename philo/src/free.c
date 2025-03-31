/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:07:41 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/31 12:07:44 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_data *data, int status)
{
	unsigned int	i;
	t_philo			*cur;
	t_philo			*last;

	if (data->check)
		free(data->check);
	if (!data->philo_first)
		return (status);
	cur = data->philo_first;
	i = 0;
	while (i < data->philo_amount)
	{
		if (cur->fork)
		{
			if (pthread_mutex_destroy(cur->fork))
				return (FLS);
			free(cur->fork);
		}
		last = cur;
		cur = cur->next;
		free(last);
		i++;
	}
	pthread_mutex_destroy(data->lock);
	return (free(data->lock), status);
}

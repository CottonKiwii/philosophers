/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:33:36 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/20 17:55:53 by jwolfram         ###   ########.fr       */
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
		last = NULL;
		i++;
	}
	return (status);
}

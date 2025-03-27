/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:14:38 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/27 15:46:49 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_data *data, unsigned long ms)
{
	unsigned long	now;

	now = gettime(0);
	while (1)
	{
		pthread_mutex_lock(data->lock);
		if (!data->end_program || gettime(now) >= ms)
			break ;
		pthread_mutex_unlock(data->lock);
	}
	pthread_mutex_unlock(data->lock);
}

t_philo *get_philo(t_data *data, unsigned int i)
{
	t_philo *cur;

	cur = data->philo_first;
	while (cur->idx != i)
		cur = cur->next;
	return (cur);
}

static int	is_overflowing(char *str)
{
	int		i;
	char	*uint;

	uint = NULL;
	if (ft_strlen(str) > 10)
		return (TR);
	if (ft_strlen(str) < 10)
		return (FLS);
	uint = ft_strncpy(uint, "4294967295", 11);
	if (!uint)
		return (FLS);
	i = 0;
	while (str[i])
	{
		if (str[i] > uint[i])
			return (free(uint), TR);
		i++;
	}
	return (free(uint), FLS);
}

int	is_valid(char *str)
{
	if (!str)
		return (TR);
	if (!is_overflowing(str))
		return (FLS);
	if (!ft_atoi(str))
		return (FLS);
	return (TR);
}

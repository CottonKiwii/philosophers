/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:14:38 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/17 13:18:18 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettime(unsigned long start)
{
	struct timeval	cur;
	unsigned long	time;

	gettimeofday(&cur, NULL);
	time = cur.tv_sec * 1000 + cur.tv_usec / 1000;
	if (start)
		return (time - start);
	return (time);
}

static int	is_overflowing(char *str)
{
	int		i;
	char	*ulong;

	ulong = NULL;
	if (ft_strlen(str) > 10)
		return (TR);
	if (ft_strlen(str) < 10)
		return (FLS);
	ulong = ft_strncpy(ulong, "4294967295", 11);
	if (!ulong)
		return (FLS);
	i = 0;
	while (str[i])
	{
		if (str[i] > ulong[i])
			return (free(ulong), TR);
		i++;
	}
	return (free(ulong), FLS);
}

int	is_valid(char *str)
{
	int		i;

	if (!str)
		return (TR);
	if (!is_overflowing(str))
		return (FLS);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FLS);
		i++;
	}
	return (TR);
}

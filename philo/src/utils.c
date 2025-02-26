/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:10 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 13:57:15 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	overflow_check;

	if (!nmemb || !size)
		return (malloc(0));
	overflow_check = nmemb * size;
	if (overflow_check / size != nmemb)
		return (NULL);
	res = (void *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	return (memset(res, 0, nmemb * size), res);
}

static int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;	
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

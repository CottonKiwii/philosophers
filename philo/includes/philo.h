/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:18:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:05:15 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				nbr;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_philo	*first;
	pthread_mutex_t	fork;
}	t_philo;

int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	*ft_calloc(size_t nmemb, size_t size);

#endif

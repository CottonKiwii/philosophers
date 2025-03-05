/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:18:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/05 16:06:14 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

# define TR 0
# define FLS 1

typedef struct s_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	eat_amount;
	struct timeval	start;
}	t_time;

typedef struct s_philo
{
	unsigned int	nbr;
	unsigned int	amount;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock;
	struct s_philo	*next;
	t_time			*time;
}	t_philo;

typedef struct s_data
{
	char			**argv;
	t_philo			*philo_first;
	t_philo			*philo_last;
	t_time			*time;
}	t_data;

void			time_init(t_data *data);
int				list_init(t_data *data);
int				routine_init(t_data *data);

void			*philo_routine(void *arg);

/* UTILS */
int				ft_strlen(char *str);
unsigned int	ft_atoi(char *str);
char			*ft_strncpy(char *dest, char *src, int n);
void			*ft_calloc(size_t nmemb, size_t size);

int				is_valid(char *str);
long			gettime(struct timeval start);

#endif

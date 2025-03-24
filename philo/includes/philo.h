/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:18:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/24 17:57:26 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TR 0
# define FLS 1

typedef enum e_msg
{
	DEATH,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_msg;


typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	*fork;
	unsigned int	idx;
	unsigned int	philo_amount;
	unsigned long	start;
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned int	eat_amount;
	struct s_philo	*next;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo_first;
	pthread_mutex_t	*lock;
	unsigned int	philo_amount;
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned int	eat_amount;
	unsigned long	*check;
	unsigned long	start;
	int				end_program;
}	t_data;

int				data_init(t_data *data, char **argv);
int				list_init(t_data *data);
int				pthread_init(t_philo *philo);

int				check_loop(t_data *data);
int				check_time(t_data *data);
int				update_time(t_philo *philo);

int				routine_init(t_data *data);
void			*philo_routine(void *arg);

/* UTILS */
int				ft_strlen(char *str);
unsigned int	ft_atoi(char *str);
char			*ft_strncpy(char *dest, char *src, int n);
void			*ft_calloc(size_t nmemb, size_t size);

int				is_valid(char *str);
unsigned long	gettime(unsigned long start);
void			ft_sleep(t_data *data, unsigned long ms);
int				put_msg(t_msg status, t_philo *philo, t_data *data, unsigned int idx);
t_philo			*get_philo(t_data *data, unsigned int i);

/* FREE */
int				free_all(t_data *data, int status);

#endif

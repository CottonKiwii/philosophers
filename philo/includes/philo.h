/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:18:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/21 17:29:32 by jwolfram         ###   ########.fr       */
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
	struct s_philo	*next;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo_first;
	pthread_mutex_t	*lock;
	unsigned int	philo_amount;
	unsigned long	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	eat_amount;
	unsigned long	*check;
	unsigned long	start;
	int				end_program;
}	t_data;

int				data_init(t_data *data, char **argv);
int				list_init(t_data *data);
int				routine_init(t_data *data);

int				check_loop(t_data *data);
int				check_time(t_data *data);
int				update_time(t_philo *philo);

void			*philo_routine(void *arg);

/* UTILS */
int				ft_strlen(char *str);
unsigned int	ft_atoi(char *str);
char			*ft_strncpy(char *dest, char *src, int n);
void			*ft_calloc(size_t nmemb, size_t size);

int				is_valid(char *str);
unsigned long	gettime(unsigned long start);
void			ft_sleep(t_data *data, unsigned long ms);
int				put_msg(t_msg status, t_data *data, int idx);
t_philo			*get_philo(t_data *data, unsigned int i);

/* FREE */
int				free_all(t_data *data, int status);

#endif

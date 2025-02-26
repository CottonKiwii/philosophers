/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:19:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:58:31 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo)
{
	t_philo	*cur;

	cur = philo->first;
	printf("********PHILOSOPHERS********\n");
	printf("PHILO %d exists\n", philo->nbr);
	while (cur->nbr != 1)
	{
		printf("PHILO %d exists\n", philo->nbr);
		cur = cur->next;
	}
}

t_philo	*philo_allocate(void)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	return (philo);
}

void	philo_init(t_philo *philo, int	amount)
{
	int	i;
	t_philo	*last;

	i = 1;
	while (i <= amount)
	{
		philo = philo_allocate();
		if (i == 1)
			philo->first = philo;
		else if (i == amount)
		{
			philo->next = philo->first;
			philo->prev = last;
		}
		else
		{
			philo->first = last->first;
			philo->next = NULL;
			philo->prev = last;
		}
		last = philo;
		philo->nbr = i;
		i++;
		philo = philo->next;
	}
}

void	*routine_init(void	*arg)
{
	char	**argv;
	t_philo	*philo;

	philo = NULL;
	argv = (char **)arg;
	philo_init(philo, ft_atoi(argv[1]));
	print_philo(philo);
	return (NULL);
}

int	pthread_init(char **argv)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	thread = (pthread_t *)ft_calloc((ft_atoi(argv[1]) + 1), sizeof(pthread_t));
	if (!thread)
		return (1);
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&(thread[i]), NULL, &routine_init, argv))
			return (1);
		if (pthread_join(thread[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (1);
	pthread_init(argv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:19:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/07 15:24:41 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_init(void	*arg)
{
	(void)arg;
	printf("Philosopher was created\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	int			status;
	pthread_t	*thread;

	if (argc < 5)
		return (1);
	i = 0;
	thread = (pthread_t *)malloc((ft_atoi(argv[1]) + 1) * sizeof(pthread_t));
	if (!thread)
		return (1);
	while (i < ft_atoi(argv[1]))
	{
		status = pthread_create(&(thread[i]), NULL, &routine_init, NULL);
		pthread_join(thread[i], NULL);
		i++;
	}
}

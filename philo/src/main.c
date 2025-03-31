/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/31 12:07:59 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_data *data)
{
	int				status;
	unsigned int	i;
	t_philo			*philo;

	if (list_init(data))
		return (free_all(data, FLS));
	status = routine_init(data);
	philo = data->philo_first;
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_join(philo->id, NULL))
			return (FLS);
		philo = philo->next;
		i++;
	}
	return (status);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (printf("philo: invalid arguments\n"), FLS);
	if (is_valid(argv[1]) || is_valid(argv[2]) || is_valid(argv[3])
		|| is_valid(argv[4]) || is_valid(argv[5]))
		return (printf("philo: invalid arguments\n"), FLS);
	if (data_init(&data, argv))
		return (FLS);
	if (philo(&data))
		return (FLS);
	return (free_all(&data, TR));
}

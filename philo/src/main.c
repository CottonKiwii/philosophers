/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:19:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/20 17:25:18 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_data *data)
{
	if (list_init(data))
		return (free_all(data, FLS));
	if (routine_init(data))
		return (FLS);
	return (TR);
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

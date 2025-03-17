/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:19:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/03/17 13:37:50 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_data *data)
{
	if (time_init(data))
		return (free(data->time), FLS);
	if (list_init(data))
		return (free_time(data->time), FLS);
	if (routine_init(data))
		return (FLS); // free nodes
	return (TR);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (FLS); // print invalid arg
	if (is_valid(argv[1]) || is_valid(argv[2]) || is_valid(argv[3]) 
		|| is_valid(argv[4]) || is_valid(argv[5]))
		return (FLS); // print invalid arg
	data.argv = argv;
	if (philo(&data))
		return (FLS);
	return (TR);
}

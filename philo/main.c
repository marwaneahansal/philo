/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/19 06:27:51 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error\n"), 1);
	data = init_philos_data(argc, argv);
	if (!data)
		return (1);
	if (create_philos(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	if (create_philos_threads(data))
		return (1);
	if (check_dying_philos(data))
		return (1);
	if (join_threads(data))
		return (1);
	if (destroy_mutexes(data))
		return (1);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}
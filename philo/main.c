/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/31 01:18:26 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid Arguments\n"), 1);
	data = init_philos_data(argc, argv);
	if (!data)
		return (1);
	printf("philos_nb ==> %d\n", data->philos_nb);
	printf("time_to_die ==> %d\n", data->time_to_die);
	printf("time_to_eat ==> %d\n", data->time_to_eat);
	printf("time_to_sleep ==> %d\n", data->time_to_sleep);
	printf("nb_times_of_eating ==> %d\n", data->nb_times_of_eating);
	free(data);
	return (0);
}
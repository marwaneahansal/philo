/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 15:46:23 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&data->state, NULL);
	pthread_mutex_init(&data->nb_eat, NULL);
	pthread_mutex_init(&data->last_eat, NULL);
	return (0);
}

int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1);
		i++;
	}
	pthread_mutex_destroy(&data->state);
	pthread_mutex_destroy(&data->nb_eat);
	pthread_mutex_destroy(&data->last_eat);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->is_philo_dead)
		return (1);
	while (i < data->philos_nb)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	detach_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_detach(data->philos[i].thread))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error\n"), 1);
	data = init_philos_data(argc, argv);
	if (!data)
		return (printf("Error\n"), 1);
	if (create_philos(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	if (create_philos_threads(data))
		return (1);
	if (check_dying_philos(data))
		return (detach_philos(data), 1);
	if (join_threads(data))
		return (1);
	if (destroy_mutexes(data))
		return (1);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}

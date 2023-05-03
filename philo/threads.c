/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:46 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:09:53 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = get_ms_time();
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	check_eat_time(t_data *data, int i)
{
	pthread_mutex_lock(&data->nb_eat);
	if (data->nb_times_of_eating != -1
		&& data->philos[i].eat_count == data->nb_times_of_eating)
		return (pthread_mutex_unlock(&data->nb_eat), 1);
	pthread_mutex_unlock(&data->nb_eat);
	return (0);
}

int	check_dying_philos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->philos_nb)
	{
		if (check_eat_time(data, i))
			j++;
		if (check_if_philo_dead(data, i))
			return (1);
		i++;
		if (j == data->philos_nb)
			return (1);
		if (i == data->philos_nb)
		{
			i = 0;
			j = 0;
		}
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		do_philo_routine(philo);
		usleep(500);
	}
	return (NULL);
}

int	create_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]))
			return (1);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < data->philos_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]))
			return (1);
		i += 2;
	}
	return (0);
}

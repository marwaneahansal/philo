/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:46 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/25 00:34:11 by mahansal         ###   ########.fr       */
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
	if (data->nb_times_of_eating != -1
		&& data->philos[i].eat_count == data->nb_times_of_eating)
	{
		if (detach_philos(data))
			return (1);
		return (1);
	}
	return (0);
}

int	check_dying_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (check_eat_time(data, i))
			return (1);
		if (get_ms_time() - data->philos[i].last_eat_time > data->time_to_die)
		{
			pthread_mutex_lock(&data->state);
			printf("%ld \t %d \t %s\n",
				get_ms_time() - data->start_time,
				data->philos[i].id, "has died");
			data->is_philo_dead = 1;
			if (detach_philos(data))
				return (1);
			return (1);
		}
		i++;
		if (i == data->philos_nb)
			i = 0;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->philos_nb]);
		print_state(philo, "has taken a fork", philo->id);
		print_state(philo, "has taken a fork", philo->id);
		print_state(philo, "is eating", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_eat);
		philo->eat_count++;
		philo->last_eat_time = get_ms_time();
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->philos_nb]);
		print_state(philo, "is sleeping", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_sleep);
		print_state(philo, "is thinking", philo->id);
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

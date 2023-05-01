/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:46 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/01 16:20:29 by mahansal         ###   ########.fr       */
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
		pthread_mutex_lock(&data->last_eat);
		if (get_ms_time() - data->philos[i].last_eat_time > data->time_to_die)
		{
			pthread_mutex_lock(&data->state);
			printf("%ld \t %d \t %s\n",
				get_ms_time() - data->start_time,
				data->philos[i].id, "has died");
			pthread_mutex_unlock(&data->last_eat);
			return (1);
		}
		pthread_mutex_unlock(&data->last_eat);
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
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print_state(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->philos_nb]);
		print_state(philo, "has taken a fork", philo->id);
		print_state(philo, "is eating", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->nb_eat);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->nb_eat);
		pthread_mutex_lock(&philo->data->last_eat);
		philo->last_eat_time = get_ms_time();
		pthread_mutex_unlock(&philo->data->last_eat);
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
	usleep(1000);
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

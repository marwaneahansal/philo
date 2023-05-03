/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:38:33 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:12:33 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleep_time(long start_time, long end_time)
{
	while (get_ms_time() - start_time < end_time)
		usleep(500);
}

void	do_philo_routine(t_philo *philo)
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
}

int	check_if_philo_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->last_eat);
	if (get_ms_time() - data->philos[i].last_eat_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->state);
		printf("%ld \t %d \t %s\n",
			get_ms_time() - data->start_time,
			data->philos[i].id, "died");
		pthread_mutex_unlock(&data->last_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->last_eat);
	return (0);
}

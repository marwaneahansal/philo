/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:46 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/15 03:06:33 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_philos(t_data *data)
{
	int i;

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

int	is_philo_dead(long current_time, t_philo *philo)
{
	// printf("current_time: %ld - last: %ld\n", current_time, philo->last_eat_time);
	// printf("id: %d - timetodie %d - current_time - last: %ld\n", philo->id, philo->data->time_to_die, current_time - philo->last_eat_time );
	if (current_time - philo->last_eat_time > philo->data->time_to_die)
		return (1);
	return (0);
}

long  get_ms_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void sleep_time(long start_time, long end_time)
{
	while (get_ms_time() - start_time < end_time);
}

void  print_state(t_philo *philo, char *state, int philo_id)
{
	pthread_mutex_lock(&philo->data->state);
	printf("%ld \t %d \t %s\n", get_ms_time() - philo->data->start_time, philo_id, state);
	pthread_mutex_unlock(&philo->data->state);
}

int	detach_philos(t_data *data)
{
	int	i;

	i = 0;
	// printf("detaching\n");
	while (i < data->philos_nb)
	{
		if (pthread_detach(data->philos[i].thread))
			return (1);
		i++;
	}
	return (0);
}

int	check_dying_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		if (get_ms_time() - data->philos[i].last_eat_time > data->time_to_die)
		{
			print_state(&data->philos[i], "has died", data->philos[i].id);
			data->is_philo_dead = 1;
			// pthread_mutex_unlock(&philo->data->state);
			if (detach_philos(data))
				return (1);
			exit(1);
		}
		i++;
	}
	return (0);
}

int	check_is_philo_dying(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (get_ms_time() - philo->last_eat_time > data->time_to_die)
	{
		print_state(philo, "has died", philo->id);
		data->is_philo_dead = 1;
		if (detach_philos(data))
			return (1);
		exit(1);
	}
	return (0);
}

void  *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (check_is_philo_dying(philo))
			return (NULL);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print_state(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->philos_nb]);
		print_state(philo, "has taken a fork", philo->id);
		print_state(philo, "is eating", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_eat);
		philo->eat_count++;
		philo->last_eat_time = get_ms_time();
		print_state(philo, "is sleeping", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_sleep);
		print_state(philo, "is thinking", philo->id);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->philos_nb]);
		usleep(500);
	}
	return (NULL);
}

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

int create_philos_threads(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
			return (1);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < data->philos_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
			return (1);
		i += 2;
	}
	return (0);
}
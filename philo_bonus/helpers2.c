/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:17:07 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:43:40 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_philo *philo, char *state, int philo_id)
{
	sem_wait(philo->data->state);
	printf("%ld \t %d \t %s\n",
		get_ms_time() - philo->data->start_time, philo_id, state);
	sem_post(philo->data->state);
}

void	sleep_time(long start_time, long end_time)
{
	while (get_ms_time() - start_time < end_time)
		usleep(500);
}

int	check_eat_time(t_data *data, int i)
{
	sem_wait(data->nb_eat);
	if (data->nb_times_of_eating != -1
		&& data->philos[i].eat_count == data->nb_times_of_eating)
	{
		sem_post(data->nb_eat);
		return (1);
	}
	sem_post(data->nb_eat);
	return (0);
}

void	kill_processes(t_data *data, int created_processes)
{
	int	i;
	int	processess_nb;

	i = 0;
	processess_nb = data->philos_nb;
	if (created_processes != -1)
		processess_nb = created_processes;
	while (i < processess_nb)
	{
		if (data->philos[i].process_id != -1)
			kill(data->philos[i].process_id, SIGTERM);
		i++;
	}
}

void	close_semaphors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		sem_close(data->philos[i].sem_eat_count);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->state);
	sem_close(data->nb_eat);
	sem_close(data->last_eat);
}

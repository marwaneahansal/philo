/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:31:21 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:46:56 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_odd_processess(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		data->philos[i].process_id = fork();
		if (data->philos[i].process_id == -1)
			return (kill_processes(data, i), 1);
		if (data->philos[i].process_id == 0)
		{
			routine(&data->philos[i]);
			exit(0);
		}
		i += 2;
	}
	return (0);
}

int	create_even_processess(t_data *data)
{
	int	i;

	i = 1;
	usleep(500);
	i = 1;
	while (i < data->philos_nb)
	{
		data->philos[i].process_id = fork();
		if (data->philos[i].process_id == -1)
			return (kill_processes(data, i), 1);
		if (data->philos[i].process_id == 0)
		{
			routine(&data->philos[i]);
			exit(0);
		}
		i += 2;
	}
	return (0);
}

void	*check_eat_count(void *arg)
{
	int			j;
	t_data		*data;

	j = 0;
	data = (t_data *) arg;
	if (data->nb_times_of_eating != -1)
	{
		check_odd_eat_count(data);
		usleep(500);
		check_even_eat_count(data);
		kill_processes(data, -1);
		exit(0);
	}
	return (NULL);
}

void	check_odd_eat_count(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->philos_nb)
	{
		while (j < data->nb_times_of_eating)
		{
			sem_wait(data->philos[i].sem_eat_count);
			usleep(500);
			j++;
		}
		i += 2;
	}
}

void	check_even_eat_count(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < data->philos_nb)
	{
		while (j < data->nb_times_of_eating)
		{
			sem_wait(data->philos[i].sem_eat_count);
			usleep(500);
			j++;
		}
		i += 2;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 07:01:38 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 15:55:02 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_numeric(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_data_struct(t_data *data)
{
	data->philos_nb = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->nb_times_of_eating = -1;
	data->start_time = 0;
	data->is_philo_dead = 0;
	data->philos = 0;
}

t_data	*init_philos_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_data_struct(data);
	if (!check_args(argc, argv))
		return (free(data), NULL);
	if (argc == 5 || argc == 6)
	{
		data->philos_nb = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->nb_times_of_eating = ft_atoi(argv[5]);
		data->start_time = get_ms_time();
		data->philos = malloc(sizeof(t_philo) * data->philos_nb);
	}
	return (data);
}

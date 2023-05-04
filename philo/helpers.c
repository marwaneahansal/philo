/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:01:23 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 15:44:27 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->philos = NULL;
	data->forks = NULL;
	data->start_time = 0;
	data->is_philo_dead = 0;
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
		data->philos = malloc(sizeof(t_philo) * data->philos_nb);
		data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nb);
		data->start_time = get_ms_time();
	}
	return (data);
}

void	print_state(t_philo *philo, char *state, int philo_id)
{
	pthread_mutex_lock(&philo->data->state);
	printf("%ld \t %d \t %s\n",
		get_ms_time() - philo->data->start_time, philo_id, state);
	pthread_mutex_unlock(&philo->data->state);
}

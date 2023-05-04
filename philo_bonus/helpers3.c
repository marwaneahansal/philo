/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:43:10 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 17:32:26 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		data->philos[i].process_id = -1;
		i++;
	}
	return (0);
}

void	unlink_semaphors(t_data *data)
{
	int		i;
	char	*sem_name;

	i = 0;
	while (i < data->philos_nb)
	{
		sem_name = ft_itoa(data->philos[i].id);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	sem_unlink("forks");
	sem_unlink("state");
	sem_unlink("nb_eat");
	sem_unlink("last_eat");
}

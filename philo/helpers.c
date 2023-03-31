/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:01:23 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/31 01:19:02 by mahansal         ###   ########.fr       */
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

int  check_args(int argc, char **argv)
{
  int  i;

  i = 1;
  while (i < argc)
  {
    if (!is_numeric(argv[i]) || ft_atoi(argv[i]) <= 0)
    {
      printf("Error: Invalid Arguments\n");
      return (0);
    }
    i++;
  }
  return (1);
}

t_data  *init_philos_data(int argc, char **argv)
{
  t_data  *data;

  data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philos_nb = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->nb_times_of_eating = -1;
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
	}
  return (data);
}
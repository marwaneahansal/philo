/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/10 09:40:37 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_numeric(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int	i;
	t_philos	*philos;

	i = 1;
	philos = malloc(sizeof(t_philos));
	philos->philos_nb = 0;
	philos->time_to_die = 0;
	philos->time_to_eat = 0;
	philos->time_to_sleep = 0;
	philos->nb_times_of_eating = 0;

	if (argc == 5 || argc == 6)
	{
		// check for valid argv and initialze data
		while (i < argc)
		{
			if (!is_numeric(argv[i]) || ft_atoi(argv[i]) <= 0)
			{
				printf("Error: Invalid Arguments\n");
				return (1);
			}
			i++;
		}
		philos->philos_nb = ft_atoi(argv[1]);
		philos->time_to_die = ft_atoi(argv[2]);
		philos->time_to_eat = ft_atoi(argv[3]);
		philos->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philos->nb_times_of_eating = ft_atoi(argv[5]);
	}
	printf("philos_nb ==> %d\n", philos->philos_nb);
	printf("time_to_die ==> %d\n", philos->time_to_die);
	printf("time_to_eat ==> %d\n", philos->time_to_eat);
	printf("time_to_sleep ==> %d\n", philos->time_to_sleep);
	printf("nb_times_of_eating ==> %d\n", philos->nb_times_of_eating);
	free(philos);
	return (0);
}
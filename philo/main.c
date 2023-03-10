/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/10 09:33:00 by mahansal         ###   ########.fr       */
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

	i = 1;
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
		printf("Got here!!!!\n");
	}
	return (0);
}
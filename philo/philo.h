/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:35:57 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/31 01:13:59 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
  int philos_nb;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int nb_times_of_eating;
} t_data;

int	ft_atoi(const char *str);

int	is_numeric(char *str);
int  check_args(int argc, char **argv);
t_data  *init_philos_data(int argc, char **argv);

#endif
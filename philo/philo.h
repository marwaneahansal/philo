/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:35:57 by mahansal          #+#    #+#             */
/*   Updated: 2023/03/10 09:24:49 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philos
{
  int philos_nb;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int time_of_eating;
} t_philos ;

int	ft_atoi(const char *str);
int	is_numeric(char *str);

#endif
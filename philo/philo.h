/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:35:57 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/03 23:15:08 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

struct s_philo;
struct s_data;

typedef struct s_philo
{
  int id;
  pthread_t thread;
  int eat_count;
  int last_eat_time;
  struct s_data *data;
} t_philo;

typedef struct s_data
{
  int philos_nb;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int nb_times_of_eating;
  long  start_time;
  t_philo *philos;
  pthread_mutex_t *forks;
  pthread_mutex_t state;
} t_data;



int	ft_atoi(const char *str);

int	is_numeric(char *str);
int  check_args(int argc, char **argv);
t_data  *init_philos_data(int argc, char **argv);

int create_philos_threads(t_data *data);
long  get_ms_time();

#endif
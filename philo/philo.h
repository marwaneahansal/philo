/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:35:57 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:10:11 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eat_count;
	long			last_eat_time;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philos_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_of_eating;
	long			start_time;
	int				is_philo_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
	pthread_mutex_t	nb_eat;
	pthread_mutex_t	last_eat;
}	t_data;

int		ft_atoi(const char *str);

int		is_numeric(char *str);
int		check_args(int argc, char **argv);

int		create_philos_threads(t_data *data);
int		init_mutexes(t_data *data);
int		destroy_mutexes(t_data *data);
int		join_threads(t_data *data);
int		create_philos(t_data *data);
int		check_dying_philos(t_data *data);
int		detach_philos(t_data *data);
void	sleep_time(long start_time, long end_time);

void	print_state(t_philo *philo, char *state, int philo_id);
long	get_ms_time(void);
void	do_philo_routine(t_philo *philo);
int		check_if_philo_dead(t_data *data, int i);

t_data	*init_philos_data(int argc, char **argv);

#endif
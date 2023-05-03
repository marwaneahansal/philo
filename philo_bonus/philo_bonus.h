/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 06:55:18 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/03 23:46:05 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int				id;
	pid_t			process_id;
	int				eat_count;
	long			last_eat_time;
	sem_t			*sem_eat_count;
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
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*state;
	sem_t			*nb_eat;
	sem_t			*last_eat;
	pthread_t		state_routine;
}	t_data;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
long	get_ms_time(void);
t_data	*init_philos_data(int argc, char **argv);
int		create_philos(t_data *data);
void	kill_processes(t_data *data, int created_processes);
void	close_semaphors(t_data *data);

int		create_odd_processess(t_data *data);
int		create_even_processess(t_data *data);
void	check_odd_eat_count(t_data *data);
void	check_even_eat_count(t_data *data);
void	*check_eat_count(void *arg);

int		create_philos(t_data *data);
void	print_state(t_philo *philo, char *state, int philo_id);
void	sleep_time(long start_time, long end_time);
void	routine(t_philo *philo);

#endif

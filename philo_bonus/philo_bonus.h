/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 06:55:18 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/26 07:12:24 by mahansal         ###   ########.fr       */
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
# include <sys/wait.h>

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int				id;
	pid_t			process_id;
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
	struct s_philo	*philos;
}	t_data;

int		ft_atoi(const char *str);
long	get_ms_time(void);
t_data	*init_philos_data(int argc, char **argv);
int	create_philos(t_data *data);

# endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:22:54 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 17:32:50 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dying_philos(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *) arg;
	while (1)
	{
		sem_wait(philo->data->last_eat);
		if (get_ms_time() - philo->last_eat_time > philo->data->time_to_die)
		{
			sem_wait(philo->data->state);
			printf("%ld \t %d \t %s\n",
				get_ms_time() - philo->data->start_time,
				philo->data->philos[i].id, "died");
			philo->data->is_philo_dead = 1;
			sem_post(philo->data->last_eat);
			exit(1);
		}
		sem_post(philo->data->last_eat);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->data->state_routine, NULL,
		&check_dying_philos, philo);
	while (1)
	{
		sem_wait(philo->data->forks);
		print_state(philo, "has taken a fork", philo->id);
		sem_wait(philo->data->forks);
		print_state(philo, "has taken a fork", philo->id);
		print_state(philo, "is eating", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_eat);
		sem_post(philo->sem_eat_count);
		sem_wait(philo->data->nb_eat);
		philo->eat_count++;
		sem_post(philo->data->nb_eat);
		sem_wait(philo->data->last_eat);
		philo->last_eat_time = get_ms_time();
		sem_post(philo->data->last_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_state(philo, "is sleeping", philo->id);
		sleep_time(get_ms_time(), philo->data->time_to_sleep);
		print_state(philo, "is thinking", philo->id);
	}
	pthread_join(philo->data->state_routine, NULL);
}

void	init_semaphors(t_data *data)
{
	int		i;
	char	*sem_name;

	unlink_semaphors(data);
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos_nb);
	data->state = sem_open("state", O_CREAT, 0644, 1);
	data->nb_eat = sem_open("nb_eat", O_CREAT, 0644, 1);
	data->last_eat = sem_open("last_eat", O_CREAT, 0644, 1);
	i = 0;
	while (i < data->philos_nb)
	{
		sem_name = ft_itoa(data->philos[i].id);
		data->philos[i].sem_eat_count
			= sem_open(sem_name, O_CREAT, 0644, 0);
		free(sem_name);
		i++;
	}
}

void	wait_childs(t_data *data)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			kill_processes(data, -1);
	}
}

int	main(int argc, char **argv)
{
	t_data			*data;
	pthread_t		thread;

	data = NULL;
	if (argc != 5 && argc != 6)
		return (printf("Error\n"), 1);
	data = init_philos_data(argc, argv);
	if (!data)
		return (printf("Error\n"), 1);
	if (create_philos(data))
		return (1);
	init_semaphors(data);
	pthread_create(&thread, NULL, &check_eat_count, data);
	if (create_odd_processess(data) || create_even_processess(data))
		return (printf("Error\n"), 1);
	pthread_join(thread, NULL);
	wait_childs(data);
	close_semaphors(data);
	free(data->philos);
	free(data);
	return (0);
}

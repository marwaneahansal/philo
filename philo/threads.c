/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:46 by mahansal          #+#    #+#             */
/*   Updated: 2023/04/05 01:15:07 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_philos(t_data *data)
{
  int i;

  i = 0;
  while (i < data->philos_nb)
  {
    data->philos[i].id = i + 1;
    data->philos[i].eat_count = 0;
    data->philos[i].last_eat_time = 0;
    data->philos[i].data = data;
    i++;
  }
  return (0);
}

long  get_ms_time()
{
  struct timeval time;

  gettimeofday(&time, NULL);
  return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void sleep_time(long start_time, long end_time)
{
  while (get_ms_time() - start_time < end_time)
  {
    // printf("end_time: %ld\n", get_ms_time() - start_time);
    usleep(100);
  }
}

void  print_state(t_philo *philo, char *state)
{
  pthread_mutex_lock(&philo->data->state);
  printf("%ld \t %d \t %s\n", get_ms_time() - philo->data->start_time, philo->id, state);
  pthread_mutex_unlock(&philo->data->state);
}

void  *routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  while (1)
  {
    pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->philos_nb]);
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    sleep_time(get_ms_time(), philo->data->time_to_eat);
    philo->eat_count++;
    philo->last_eat_time = get_ms_time();
    print_state(philo, "is sleeping");
    sleep_time(get_ms_time(), philo->data->time_to_sleep);
    print_state(philo, "is thinking");
    pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->philos_nb]);
  }
  return (NULL);
}

int create_philos_threads(t_data *data)
{
  int i;

  i = 0;
  if (create_philos(data))
    return (1);
  int j = 0;
  while (j < data->philos_nb)
  {
    if (pthread_mutex_init(&data->forks[j], NULL))
      return (1);
    j++;
  }
  pthread_mutex_init(&data->state, NULL);
  while (i < data->philos_nb)
  {
    if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
      return (1);
    i++;
  }
  i = 0;
  while (i < data->philos_nb)
  {
    if (pthread_join(data->philos[i].thread, NULL))
      return (1);
    i++;
  }
  j = 0;
  while (j < data->philos_nb)
  {
    if (pthread_mutex_destroy(&data->forks[j]))
      return (1);
    j++;
  }
  pthread_mutex_destroy(&data->state);
  return (0);
}
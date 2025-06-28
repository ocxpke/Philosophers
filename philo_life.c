/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:23:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void philo_says(t_philo_single *philo, char *message) {
  pthread_mutex_lock(&(philo->check_if_alive));
  if (philo->alive) {
    pthread_mutex_unlock(&(philo->check_if_alive));
    pthread_mutex_lock(&philo->common_args->kylix);
    pthread_mutex_lock(&(philo->common_args->someone_died));
    if (!philo->common_args->someone_dead)
      printf("[%d] %d %s\n", get_act_time() - philo->common_args->epoch,
             philo->id + 1, message);
    pthread_mutex_unlock(&(philo->common_args->someone_died));
    pthread_mutex_unlock(&philo->common_args->kylix);
    return;
  }
  pthread_mutex_unlock(&(philo->check_if_alive));
}

void philo_meal(t_philo_single *philo) {
  int first_to_take;
  int second_to_take;

  assign_order_forks(philo, &first_to_take, &second_to_take);
  pthread_mutex_lock(&(philo->common_args->forks[first_to_take]));
  philo_says(philo, "has taken a fork");
  if (philo->id == philo->id_left)
    return (wait_till_dead(philo));
  pthread_mutex_lock(&(philo->common_args->forks[second_to_take]));
  philo_says(philo, "has taken a fork");
  philo_says(philo, "is eating");
  pthread_mutex_lock(&(philo->check_last_meal));
  philo->last_meal_time = get_act_time();
  pthread_mutex_unlock(&(philo->check_last_meal));
  ft_usleep(philo, philo->common_args->time_to_eat);
  pthread_mutex_unlock(&(philo->common_args->forks[first_to_take]));
  pthread_mutex_unlock(&(philo->common_args->forks[second_to_take]));
  pthread_mutex_lock(&(philo->check_n_meals));
  if (philo->eat_n_times > 0)
    philo->eat_n_times--;
  pthread_mutex_unlock(&(philo->check_n_meals));
}

void *philo_life(void *philo_info) {
  t_philo_single *philo;

  philo = (t_philo_single *)philo_info;
  pthread_mutex_lock(&(philo->check_last_meal));
  philo->last_meal_time = get_act_time();
  pthread_mutex_unlock(&(philo->check_last_meal));
  pthread_mutex_lock(&(philo->check_if_alive));
  while (philo->alive && (philo->eat_n_times != 0)) {
    pthread_mutex_unlock(&(philo->check_if_alive));
    philo_says(philo, "is thinking");
    philo_meal(philo);
    philo_says(philo, "is sleeping");
    ft_usleep(philo, philo->common_args->time_to_sleep);
    pthread_mutex_lock(&(philo->check_if_alive));
  }
  pthread_mutex_unlock(&(philo->check_if_alive));
  return (NULL);
}

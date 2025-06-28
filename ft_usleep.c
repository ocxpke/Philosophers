/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:25:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:27:56 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline void ft_usleep(t_philo_single *philo, int time_to_wait) {
  int init_time;

  pthread_mutex_lock(&(philo->check_if_alive));
  if (!philo->alive) {
    pthread_mutex_unlock(&(philo->check_if_alive));
    return;
  }
  pthread_mutex_unlock(&(philo->check_if_alive));
  init_time = get_act_time();
  pthread_mutex_lock(&(philo->check_if_alive));
  while (((get_act_time() - init_time) < time_to_wait) && (philo->alive)) {
    pthread_mutex_unlock(&(philo->check_if_alive));
    usleep(time_to_wait / 4);
    pthread_mutex_lock(&(philo->check_if_alive));
  }
  pthread_mutex_unlock(&(philo->check_if_alive));
}

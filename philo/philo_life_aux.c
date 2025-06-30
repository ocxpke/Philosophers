/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:12:44 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:20:43 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
inline void assign_order_forks(t_philo_single *philo, int *first_to_take,
                               int *second_to_take) {
  *first_to_take = philo->id;
  *second_to_take = philo->id_left;
  if ((philo->id % 2) != 0) {
    *first_to_take = philo->id_left;
    *second_to_take = philo->id;
  }
}*/

inline void assign_order_forks(t_philo_single *philo, int *first_fork,
                               int *second_fork) {
  int left_fork = philo->id;
  int right_fork = (philo->id + 1) % philo->common_args->assistants;

  if (left_fork < right_fork) {
    *first_fork = left_fork;
    *second_fork = right_fork;
  } else {
    *first_fork = right_fork;
    *second_fork = left_fork;
  }
}

inline void wait_till_dead(t_philo_single *philo) {
  pthread_mutex_unlock(&(philo->common_args->forks[philo->id]));
  while (philo->alive)
    ft_usleep(philo, philo->common_args->time_to_die);
}

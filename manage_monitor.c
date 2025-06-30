/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:33:19 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/22 21:32:59 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline int all_ended_eating(t_philo_single *all_philos) {
  int ret;
  int i;

  pthread_mutex_lock(&(all_philos[0].check_n_meals));
  if (all_philos[0].eat_n_times == -1) {
    pthread_mutex_unlock(&(all_philos[0].check_n_meals));
    return (1);
  }
  pthread_mutex_unlock(&(all_philos[0].check_n_meals));
  i = 0;
  ret = 0;
  while (i < all_philos[0].common_args->assistants) {
    pthread_mutex_lock(&(all_philos[i].check_n_meals));
    if (all_philos[i].eat_n_times > 0)
      ret = 1;
    pthread_mutex_unlock(&(all_philos[i].check_n_meals));
    i++;
  }
  return (ret);
}

static inline void check_philos_status(t_philo_single *all_philos, int *loop) {
  int time_passed;
  int i;

  i = 0;
  *loop = all_ended_eating(all_philos);
  while ((i < all_philos[0].common_args->assistants) && (*loop)) {
    pthread_mutex_lock(&(all_philos[i].check_last_meal));
    time_passed = (get_act_time() - all_philos[i].last_meal_time);
    pthread_mutex_unlock(&(all_philos[i].check_last_meal));
    if (time_passed > all_philos[i].common_args->time_to_die) {
      pthread_mutex_lock(&(all_philos[i].common_args->someone_died));
      all_philos[i].common_args->someone_dead = 1;
      pthread_mutex_unlock(&(all_philos[i].common_args->someone_died));
      pthread_mutex_lock(&(all_philos[i].check_if_alive));
      all_philos[i].alive = 0;
      pthread_mutex_unlock(&(all_philos[i].check_if_alive));
      pthread_mutex_lock(&(all_philos[i].common_args->kylix));
      printf("[%d] %s%d died%s\n",
             get_act_time() - all_philos[i].common_args->epoch, ANSI_BG_BRED,
             all_philos[i].id + 1, ANSI_RESET);
      pthread_mutex_unlock(&(all_philos[i].common_args->kylix));
      *loop = 0;
    }
    i++;
  }
  usleep((all_philos[0].common_args->time_to_die * 1000) / 2);
}

static inline void stop_running_philos(t_philo_single *all_philos) {
  int i;

  i = 0;
  while (i < all_philos[0].common_args->assistants) {
    pthread_mutex_lock(&(all_philos[i].check_if_alive));
    all_philos[i].alive = 0;
    pthread_mutex_unlock(&(all_philos[i].check_if_alive));
    i++;
  }
}

void *monitoring_philos(void *philos) {
  t_philo_single *all_philos;
  int loop;

  all_philos = (t_philo_single *)philos;
  loop = 1;
  while (loop)
    check_philos_status(philos, &loop);
  stop_running_philos(all_philos);
  return (NULL);
}

void launch_philo_monitor(t_philo_single *philosophers) {
  pthread_t philo_monitor;

  pthread_create(&philo_monitor, NULL, monitoring_philos, philosophers);
  pthread_detach(philo_monitor);
}

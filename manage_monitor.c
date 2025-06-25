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

static inline int all_ended_eating(t_philosopher *all_philos) {
  int ret;
  int i;

  if (all_philos[0].eat_n_times == -1)
    return (1);
  i = 0;
  ret = 0;
  while (i < all_philos[0].assistants) {
    if (all_philos[i].eat_n_times > 0)
      ret = 1;
    i++;
  }
  return (ret);
}

static inline void check_philos_status(t_philosopher *all_philos, int *loop) {
  int time_passed;
  int i;

  i = 0;
  *loop = all_ended_eating(all_philos);
  while ((i < all_philos[0].assistants) && (*loop)) {
    pthread_mutex_lock(&(all_philos[i].check_if_dead));
    time_passed = (get_act_time() - all_philos[i].last_meal_time);
    pthread_mutex_unlock(&(all_philos[i].check_if_dead));
    if (time_passed > all_philos[i].time_to_die) {
      pthread_mutex_lock(&(all_philos[i].check_status));
      all_philos[i].exec = 0;
      pthread_mutex_unlock(&(all_philos[i].check_status));
      pthread_mutex_lock(&(all_philos[i].kylix));
      printf("[%d] %d died\n", exec_time(&all_philos[i]), all_philos[i].id + 1);
      //pthread_mutex_unlock(&(all_philos[i].kylix));
      *loop = 0;
    }
    i++;
  }
  usleep(100);
}

static inline void stop_running_philos(t_philosopher *all_philos) {
  int i;

  i = 0;
  while (i < all_philos[0].assistants) {
    all_philos[i].exec = 0;
    i++;
  }
}

void *monitoring_philos(void *philos) {
  t_philosopher *all_philos;
  int loop;

  all_philos = (t_philosopher *)philos;
  loop = 1;
  while (loop)
    check_philos_status(philos, &loop);
  stop_running_philos(all_philos);
  return (NULL);
}

void launch_philo_monitor(t_philosopher *philosophers) {
  pthread_t philo_monitor;

  pthread_create(&philo_monitor, NULL, monitoring_philos, philosophers);
  pthread_detach(philo_monitor);
}

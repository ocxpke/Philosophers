/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:22:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void free_on_error(t_philo_common *common_args,
                                 t_philo_single **philosophers, int c) {
  free(common_args->forks);
  if (c == 1) {
    free(*philosophers);
    write(2, "Error allocating the memory needed for philo threads\n", 53);
  } else
    write(2, "Error allocating the memory needed for philostructs\n", 52);
  exit(EXIT_FAILURE);
}

static inline void fill_philos(t_philo_common *common_args,
                               t_philo_single *philosophers) {
  int i;

  i = 0;
  while (i < common_args->assistants) {
    philosophers[i].id = i;
    philosophers[i].id_left = ((i + 1) % common_args->assistants);
    philosophers[i].init_time = get_act_time();
    philosophers[i].last_meal_time = philosophers[i].init_time;
    philosophers[i].eat_n_times = common_args->eat_n_times;
    philosophers[i].alive = 1;
    pthread_mutex_init(&(philosophers[i].check_if_alive), NULL);
    pthread_mutex_init(&(philosophers[i].check_last_meal), NULL);
    pthread_mutex_init(&(philosophers[i].check_n_meals), NULL);
    philosophers[i].common_args = common_args;
    i++;
  }
}

static inline void run_philos(t_philo_common *common_args,
                              t_philo_single *philosophers,
                              pthread_t *philo_threads) {
  int i;

  i = 0;

  common_args->epoch = get_act_time();
  while (i < common_args->assistants) {
    pthread_create(&(philo_threads[i]), NULL, philo_life, &(philosophers[i]));
    i++;
  }
}

void create_philos(t_philo_common *common_args, t_philo_single **philosophers,
                   pthread_t **philo_threads) {
  *philosophers = (t_philo_single *)malloc(common_args->assistants *
                                           sizeof(t_philo_single));
  if (!*philosophers)
    free_on_error(common_args, philosophers, 0);
  *philo_threads =
      (pthread_t *)malloc(common_args->assistants * sizeof(pthread_t));
  if (!*philo_threads)
    free_on_error(common_args, philosophers, 1);
  fill_philos(common_args, *philosophers);
  run_philos(common_args, *philosophers, *philo_threads);
}

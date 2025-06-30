/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:21:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "colors.h"

typedef struct s_philo_common {
  pthread_mutex_t *forks;
  pthread_mutex_t kylix;
  pthread_mutex_t someone_died;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int eat_n_times;
  int assistants;
  int epoch;
  int someone_dead;
} t_philo_common;

typedef struct s_philo_single {
  int id;
  int id_left;
  int init_time;
  int last_meal_time;
  int eat_n_times;
  int alive;
  pthread_mutex_t check_if_alive;
  pthread_mutex_t check_last_meal;
  pthread_mutex_t check_n_meals;
  t_philo_common *common_args;
} t_philo_single;

int ft_strlen(char *arg);
int ft_isdigit(int c);
long long int ft_latoi(const char *nptr);

void start_philo_t(int argc, char **argv, t_philo_common *common_args);

void create_philos(t_philo_common *common_args, t_philo_single **philosophers,
                   pthread_t **philo_threads);

void ft_usleep(t_philo_single *philo, int time_to_wait);
int get_act_time(void);
void *philo_life(void *philo_info);
void assign_order_forks(t_philo_single *philo, int *first_to_take,
                        int *second_to_take);
void wait_till_dead(t_philo_single *philo);

void launch_philo_monitor(t_philo_single *philosophers);

#endif

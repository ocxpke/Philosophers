/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/16 21:56:34 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline int check_all_num(char *arg) {
  if (!arg)
    return (0);
  int ret = 1;
  int i = 0;
  if (arg[0] == '+' || arg[0] == '-')
    i++;
  while ((i < ft_strlen(arg)) && ret) {
    if (!ft_isdigit(arg[i]))
      ret = 0;
    i++;
  }
  return (ret);
}

static int get_num(char *arg) {
  long long ret;
  if ((ft_strlen(arg) > 11) || !check_all_num(arg))
    return (-1);
  ret = ft_latoi(arg);
  if ((ret > INT_MAX) || (ret < INT_MIN))
    return (-1);
  return ((int)ret);
}

static inline void load_init_values(int argc, char **argv,
                                    t_philo_common *common_args) {
  int aux;

  aux = get_num(argv[1]);
  if (aux <= 0)
    return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
  common_args->assistants = aux;
  aux = get_num(argv[2]);
  if (aux <= 0)
    return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
  common_args->time_to_die = aux;
  aux = get_num(argv[3]);
  if (aux <= 0)
    return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
  common_args->time_to_eat = aux;
  aux = get_num(argv[4]);
  if (aux <= 0)
    return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
  common_args->time_to_sleep = aux;
  if (argc == 6) {
    aux = get_num(argv[5]);
    if (aux <= 0)
      return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
    common_args->eat_n_times = aux;
  }
}

inline static void create_mutexs(t_philo_common *common_args) {
  int i;

  i = 0;
  while (i < common_args->assistants) {
    // Creamos un mutex para cada tenedor
    pthread_mutex_init(&(common_args->forks[i]), NULL);
    i++;
  }
  // Creamos el mutex del kylix
  pthread_mutex_init(&(common_args->kylix), NULL);
  pthread_mutex_init(&(common_args->someone_died), NULL);
}

void start_philo_t(int argc, char **argv, t_philo_common *common_args) {
  common_args->eat_n_times = -1;
  load_init_values(argc, argv, common_args);
  common_args->forks = (pthread_mutex_t *)malloc(common_args->assistants *
                                                 sizeof(pthread_mutex_t));
  if (!common_args->forks)
    exit(EXIT_FAILURE);
  create_mutexs(common_args);
  common_args->someone_dead = 0;
}

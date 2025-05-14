/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:38 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/08 21:26:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv) {
  t_symposium symposium;
  t_philosopher *philosopher;
  pthread_t *philo_threads;

  if (argc < 5 || argc > 6)
    return (write(2, "Error\n", 6), 1);

  start_philo_t(argc, argv, &symposium);
  printf("Hola\n");
  create_philos(&symposium, &philosopher, &philo_threads);
  while (1)
    ;
}

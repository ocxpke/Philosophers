/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:11:15 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/02 14:36:00 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void free_philo_bonus(t_philo_bonus_common *common_args, pid_t **all_pids) {
  sem_close(common_args->sem_forks);
  sem_close(common_args->at_least_pair);
  sem_close(common_args->kylix);
  sem_close(common_args->check_someone_died);
  free(*all_pids);
  *all_pids = NULL;
}

int main(int argc, char **argv) {
  t_philo_bonus_common common_args;
  pid_t *all_pids;
  int i;
  int loop;

  if (argc < 5 || argc > 6)
    return (write(2, "Invalid arguments\n", 18), EXIT_FAILURE);
  all_pids = NULL;
  start_philo_bonus_common_t(argc, argv, &common_args);
  start_philo_bonus_individual_t(&all_pids, &common_args);
  loop = 1;
  while (loop) {
    i = 0;
    while (i < common_args.assistants) {
		//Comprobar final
      waitpid(all_pids[i], NULL, WNOHANG);
      i++;
    }
    loop = 0;
  }
  free_philo_bonus(&common_args, &all_pids);
}

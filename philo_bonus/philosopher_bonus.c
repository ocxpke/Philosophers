/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:11:15 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 13:10:36 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	free_philo_bonus(t_philo_bonus_common *common_args, pid_t **all_pids)
{
	int	i;

	sem_close(common_args->sem_forks);
	sem_close(common_args->at_least_pair);
	sem_close(common_args->kylix);
	sem_close(common_args->death);
	sem_close(common_args->n_meals);
	i = 0;
	while (i < common_args->assistants)
	{
		sem_close(common_args->destroyer_of_worlds[i]);
		i++;
	}
	free(common_args->destroyer_of_worlds);
	common_args->destroyer_of_worlds = NULL;
	free(*all_pids);
	*all_pids = NULL;
}

/**

 * @brief Sends a signal to all process that are waiting to end.
   Also waits for them to end.
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param all_pids Array of all pid_t from all process created.
 * @return Void.
 */
static void	process_finalizer(pid_t *all_pids,
		t_philo_bonus_common *common_args)
{
	int	i;

	i = 0;
	while (i < common_args->assistants)
	{
		sem_post(common_args->destroyer_of_worlds[i]);
		i++;
	}
	i = 0;
	while (i < common_args->assistants)
	{
		waitpid(all_pids[i], NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_bonus_common	common_args;
	pid_t					*all_pids;
	pthread_t				monitor_death;
	pthread_t				monitor_meals;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18), EXIT_FAILURE);
	all_pids = NULL;
	start_philo_bonus_common_t(argc, argv, &common_args);
	start_philo_bonus_individual_t(&all_pids, &common_args);
	launch_main_monitors(&monitor_death, &monitor_meals, &common_args);
	pthread_join(monitor_death, NULL);
	pthread_join(monitor_meals, NULL);
	process_finalizer(all_pids, &common_args);
	free_philo_bonus(&common_args, &all_pids);
}

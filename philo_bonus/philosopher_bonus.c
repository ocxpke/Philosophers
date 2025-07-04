/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:11:15 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/04 15:30:48 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	free_philo_bonus(t_philo_bonus_common *common_args, pid_t **all_pids)
{
	sem_close(common_args->sem_forks);
	sem_close(common_args->at_least_pair);
	sem_close(common_args->kylix);
	sem_close(common_args->death);
	free(*all_pids);
	*all_pids = NULL;
}

int	end_process_checker(pid_t *all_pids, t_philo_bonus_common *common_args)
{
	int	i;

	i = 0;
	while (i < common_args->assistants)
	{
		if (all_pids[i] != -2)
			return (1);
		i++;
	}
	return (0);
}

void	process_checker(pid_t *all_pids, t_philo_bonus_common *common_args)
{
	int		i;
	pid_t	pid_wait;

	while (end_process_checker(all_pids, common_args))
	{
		i = 0;
		usleep(1000);
		while (i < common_args->assistants)
		{
			pid_wait = 0;
			if (all_pids[i] != -2)
				pid_wait = waitpid(all_pids[i], NULL, WNOHANG);
			if (pid_wait > 0)
				all_pids[i] = -2;
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo_bonus_common	common_args;
	pid_t					*all_pids;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18), EXIT_FAILURE);
	all_pids = NULL;
	start_philo_bonus_common_t(argc, argv, &common_args);
	start_philo_bonus_individual_t(&all_pids, &common_args);
	process_checker(all_pids, &common_args);
	free_philo_bonus(&common_args, &all_pids);
}

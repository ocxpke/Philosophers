/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:42 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/04 14:24:59 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	start_philo_bonus_individual_t(pid_t **all_pids,
		t_philo_bonus_common *common_args)
{
	int		i;
	pid_t	id;

	*all_pids = (pid_t *)malloc(common_args->assistants * sizeof(pid_t));
	if (!(*all_pids))
		return (write(2, "Error allocating pid's\n", 23), exit(EXIT_FAILURE));
	common_args->epoch = get_act_time();
	i = 0;
	while (i < common_args->assistants)
	{
		id = fork();
		if (id == -1)
			return (write(2, "Error creating pipe\n", 20), exit(EXIT_FAILURE));
		else if (id == 0)
		{
			philo_life(common_args, i);
			free_philo_bonus(common_args, all_pids);
			exit(EXIT_SUCCESS);
		}
		else
			all_pids[0][i] = id;
		i++;
	}
}

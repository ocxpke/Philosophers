/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:02:43 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/01 18:05:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	someone_has_died(t_philo_single *all_philos, int *loop, int i)
{
	pthread_mutex_lock(&(all_philos[i].common_args->someone_died));
	all_philos[i].common_args->someone_dead = 1;
	pthread_mutex_unlock(&(all_philos[i].common_args->someone_died));
	pthread_mutex_lock(&(all_philos[i].check_if_alive));
	all_philos[i].alive = 0;
	pthread_mutex_unlock(&(all_philos[i].check_if_alive));
	pthread_mutex_lock(&(all_philos[i].common_args->kylix));
	printf("[%d] %s%d died%s\n", get_act_time()
		- all_philos[i].common_args->epoch, ANSI_BG_BRED, all_philos[i].id + 1,
		ANSI_RESET);
	pthread_mutex_unlock(&(all_philos[i].common_args->kylix));
	*loop = 0;
}

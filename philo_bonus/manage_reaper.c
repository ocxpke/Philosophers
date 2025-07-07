/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_reaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:02:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 13:58:53 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/**
 * @brief Waits for main process signal to end and kills the philosopher
 *
 * @param philo_thing Philo individual structure that contains all
 * the necesary data
 * @return Always NULL
 */
static void	*reaper_life(void *philo_things)
{
	t_philo_bonus_individual	*philo_stats;

	philo_stats = (t_philo_bonus_individual *)philo_things;
	sem_wait(philo_stats->common_args->destroyer_of_worlds[philo_stats->id]);
	sem_wait(philo_stats->check_alive);
	philo_stats->alive = 0;
	sem_post(philo_stats->check_alive);
	return (NULL);
}

void	launch_reaper(pthread_t *reaper, t_philo_bonus_individual *philo_stats)
{
	pthread_create(reaper, NULL, reaper_life, (void *)philo_stats);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_reaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:02:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/04 15:30:38 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*reaper_life(void *philo_things)
{
	t_philo_bonus_individual	*philo_stats;

	philo_stats = (t_philo_bonus_individual *)philo_things;
	sem_wait(philo_stats->common_args->death);
	sem_wait(philo_stats->check_alive);
	philo_stats->alive = 0;
	sem_post(philo_stats->check_alive);
	sem_post(philo_stats->common_args->death);
	return (NULL);
}

void	launch_reaper(pthread_t *reaper, t_philo_bonus_individual *philo_stats)
{
	pthread_create(reaper, NULL, reaper_life, (void *)philo_stats);
}

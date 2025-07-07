/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:11:06 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 13:58:30 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/**
 * @brief Checks if philo died of starvation
 *
 * @param philo_stats Philo individual structure that contains all
 * the necesary data
 * @return Void
 */
static void	check_last_meal(t_philo_bonus_individual *philo_stats)
{
	int	time_passed;

	sem_wait(philo_stats->check_last_meal);
	time_passed = get_act_time() - philo_stats->last_meal_time;
	sem_post(philo_stats->check_last_meal);
	if (time_passed > philo_stats->common_args->time_to_die)
	{
		sem_wait(philo_stats->check_alive);
		philo_stats->alive = 0;
		sem_post(philo_stats->check_alive);
		sem_wait(philo_stats->common_args->kylix);
		printf("[%d] %s%d died%s\n", get_act_time()
			- philo_stats->common_args->epoch, ANSI_BG_RED, philo_stats->id + 1,
			ANSI_RESET);
		sem_post(philo_stats->common_args->kylix);
	}
}

/**
 * @brief Always checks if the philo eated n times or if philo died of
 * starvation
 *
 * @param philo_thing Philo individual structure that contains all
 * the necesary data
 * @return Always NULL
 */
static void	*monitor_life(void *philo_things)
{
	t_philo_bonus_individual	*philo_stats;
	int							wait;

	philo_stats = (t_philo_bonus_individual *)philo_things;
	sem_wait(philo_stats->check_alive);
	sem_wait(philo_stats->check_n_meals);
	while (philo_stats->alive && (philo_stats->eat_n_times != 0))
	{
		sem_post(philo_stats->check_alive);
		sem_post(philo_stats->check_n_meals);
		check_last_meal(philo_stats);
		usleep(1000);
		sem_wait(philo_stats->check_alive);
		sem_wait(philo_stats->check_n_meals);
	}
	sem_post(philo_stats->check_alive);
	wait = (philo_stats->eat_n_times == 0);
	sem_post(philo_stats->check_n_meals);
	if (wait)
		sem_post(philo_stats->common_args->n_meals);
	else
		sem_post(philo_stats->common_args->death);
	return (NULL);
}

void	launch_philo_monitor(pthread_t *monitor,
		t_philo_bonus_individual *philo_stats)
{
	pthread_create(monitor, NULL, monitor_life, (void *)philo_stats);
}

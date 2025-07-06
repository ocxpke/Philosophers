/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_monitors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:46:23 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/06 14:26:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*monitor_meals_routine(void *args)
{
	t_philo_bonus_common	*common_args;
	int						i;

	common_args = (t_philo_bonus_common *)args;
	i = 0;
	while (i < common_args->assistants)
	{
		sem_wait(common_args->n_meals);
		i++;
	}
	sem_post(common_args->death);
	return (NULL);
}

void	*monitor_death_routine(void *args)
{
	t_philo_bonus_common	*common_args;
	int						i;

	common_args = (t_philo_bonus_common *)args;
	sem_wait(common_args->death);
	i = 0;
	while (i < common_args->assistants)
	{
		sem_post(common_args->n_meals);
		i++;
	}
	return (NULL);
}

void	launch_main_monitors(pthread_t *monitor_death, pthread_t *monitor_meals,
		t_philo_bonus_common *common_args)
{
	pthread_create(monitor_death, NULL, monitor_death_routine,
		(void *)common_args);
	pthread_create(monitor_meals, NULL, monitor_meals_routine,
		(void *)common_args);
}

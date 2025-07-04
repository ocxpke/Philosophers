/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:43:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/04 15:23:24 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_usleep(t_philo_bonus_individual *philo_stats, int time)
{
	int	init;

	init = get_act_time();
	sem_wait(philo_stats->check_alive);
	while (philo_stats->alive && ((get_act_time() - init) < time))
	{
		sem_post(philo_stats->check_alive);
		usleep((time * 1000) / 4);
		sem_wait(philo_stats->check_alive);
	}
	sem_post(philo_stats->check_alive);
}

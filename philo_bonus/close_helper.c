/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:27:25 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 12:37:37 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	close_aux(t_philo_bonus_common *common_args, int mode)
{
	sem_close(common_args->sem_forks);
	if (mode >= 1)
		sem_close(common_args->at_least_pair);
	if (mode >= 2)
		sem_close(common_args->kylix);
	if (mode >= 3)
		sem_close(common_args->death);
	if (mode >= 4)
		sem_close(common_args->n_meals);
	exit(EXIT_FAILURE);
}

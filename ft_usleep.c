/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:25:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:27:56 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline void	ft_usleep(t_philosopher *philo, int time_to_wait)
{
	int	init_time;

	if (!philo->exec)
		return ;
	init_time = get_act_time();
	while ((get_act_time() - init_time) < time_to_wait)
		usleep(100);
}

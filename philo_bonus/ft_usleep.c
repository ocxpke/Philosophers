/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:43:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/02 11:46:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_usleep(int time)
{
	int	init;

	init = get_act_time();
	while ((get_act_time() - init) < time)
		usleep((time * 1000) / 4);
}

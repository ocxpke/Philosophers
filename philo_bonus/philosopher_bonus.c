/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:11:15 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/01 19:56:19 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	main(int argc, char **argv)
{
	t_philo_bonus_common	common_args;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18), EXIT_FAILURE);
	start_philo_bonus_t(argc, argv, &common_args);
}

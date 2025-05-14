/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:38 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 21:23:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_symposium		symposium;
	t_philosopher	*philosopher;
	pthread_t		*philo_threads;
	int				init_time;

	init_time = get_act_time();
	/*
		if (argc < 5 || argc > 6)
			return (write(2, "Error\n", 6), 1);
		start_philo_t(argc, argv, &symposium);
		printf("Hola\n");
		create_philos(&symposium, &philosopher, &philo_threads);
	*/
	while (1)
	{
		printf("%d\n", get_act_time() - init_time);
    usleep(1000000);
	}
}

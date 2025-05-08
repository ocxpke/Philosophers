/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/08 21:32:50 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	charge_init_values(int argc, char **argv,
		t_symposium *symposium)
{
	int	aux;

	aux = ft_atoi(argv[1]);
	if (aux >= 0)
		exit(EXIT_FAILURE);
	symposium->assitants = aux;
	aux = ft_atoi(argv[2]);
	if (aux >= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_die = aux;
	aux = ft_atoi(argv[3]);
	if (aux >= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_eat = aux;
	aux = ft_atoi(argv[4]);
	if (aux >= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_sleep = aux;
	if (argc == 6)
	{
		aux = ft_atoi(argv[5]);
		if (aux >= 0)
			exit(EXIT_FAILURE);
		symposium->eat_n_times = aux;
	}
}

void	start_philo_t(int argc, char **argv, t_symposium *symposium)
{
	symposium->eat_n_times = -1;
	charge_init_values(argc, argv, symposium);
	symposium->philosophers = (t_philosopher *)malloc((symposium->assitants)
			* sizeof(t_philosopher));
	if (!symposium->philosophers)
		exit(EXIT_FAILURE);
	symposium->forks = (pthread_mutex_t *)malloc((symposium->assitants)
			* sizeof(pthread_mutex_t));
	if (!symposium->forks)
		exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 20:46:48 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	load_init_values(int argc, char **argv,
		t_symposium *symposium)
{
	int	aux;

	aux = ft_atoi(argv[1]);
	if (aux <= 0)
		exit(EXIT_FAILURE);
	symposium->assitants = aux;
	aux = ft_atoi(argv[2]);
	if (aux <= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_die = aux;
	aux = ft_atoi(argv[3]);
	if (aux <= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_eat = aux;
	aux = ft_atoi(argv[4]);
	if (aux <= 0)
		exit(EXIT_FAILURE);
	symposium->time_to_sleep = aux;
	if (argc == 6)
	{
		aux = ft_atoi(argv[5]);
		if (aux <= 0)
			exit(EXIT_FAILURE);
		symposium->eat_n_times = aux;
	}
}

inline static void	create_mutexs(t_symposium *symposium)
{
	int	i;

	i = 0;
	while (i < symposium->assitants)
	{
		pthread_mutex_init(&(symposium->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(symposium->kylix), NULL);
}

void	start_philo_t(int argc, char **argv, t_symposium *symposium)
{
	symposium->eat_n_times = -1;
	load_init_values(argc, argv, symposium);
	symposium->forks = (pthread_mutex_t *)malloc(symposium->assitants
			* sizeof(pthread_mutex_t));
	if (!symposium->forks)
		exit(EXIT_FAILURE);
	symposium->philo = (pthread_t *)malloc(symposium->assitants
			* sizeof(pthread_t));
	if (!symposium->philo)
		exit(EXIT_FAILURE);
	create_mutexs(symposium);
	symposium->eat_stack = init_eat_stack(symposium->assitants);
}

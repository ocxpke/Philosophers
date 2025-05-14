/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 20:46:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline static void	fill_philos(t_symposium *symposium,
		t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < symposium->assitants)
	{
		philosophers[i].id = i;
		philosophers[i].id_left = ((i + 1) % symposium->assitants);
		philosophers[i].forks = symposium->forks;
		philosophers[i].kylix = symposium->kylix;
		philosophers[i].time_to_die = symposium->time_to_die;
		philosophers[i].time_to_eat = symposium->time_to_eat;
		philosophers[i].time_to_sleep = symposium->time_to_sleep;
		philosophers[i].eat_n_times = symposium->eat_n_times;
		philosophers[i].eat_stack = &(symposium->eat_stack);
		i++;
	}
}

static inline void	run_philos(int assistants, t_philosopher *philosophers,
		pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < assistants)
	{
		pthread_create(&(philo_threads[i]), NULL, philo_life,
			&(philosophers[i]));
		i++;
	}
}

void	create_philos(t_symposium *symposium, t_philosopher **philosophers,
		pthread_t **philo_threads)
{
	*philosophers = (t_philosopher *)malloc(symposium->assitants
			* sizeof(t_philosopher));
	// need to free sympos
	if (!*philosophers)
		exit(EXIT_FAILURE);
	fill_philos(symposium, *philosophers);
	*philo_threads = (pthread_t *)malloc(symposium->assitants
			* sizeof(pthread_t));
	// need to free sympos & philosophers
	if (!*philo_threads)
		exit(EXIT_FAILURE);
	run_philos(symposium->assitants, *philosophers, *philo_threads);
}

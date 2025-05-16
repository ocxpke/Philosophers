/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/16 20:54:00 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline static void	fill_philos(t_symposium *symposium,
		t_philosopher *philosophers, int init_time)
{
	int	i;

	i = 0;
	while (i < symposium->assistants)
	{
		philosophers[i].id = i;
		philosophers[i].id_left = ((i + 1) % symposium->assistants);
		philosophers[i].forks = symposium->forks;
		philosophers[i].kylix = symposium->kylix;
		philosophers[i].time_to_die = symposium->time_to_die;
		philosophers[i].time_to_eat = symposium->time_to_eat;
		philosophers[i].time_to_sleep = symposium->time_to_sleep;
		philosophers[i].eat_n_times = symposium->eat_n_times;
		philosophers[i].init_time = init_time;
		philosophers[i].last_meal_time = -1;
		philosophers[i].exec = 1;
		philosophers[i].assistants = symposium->assistants;
		pthread_mutex_init(&(philosophers[i].check_status), NULL);
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
	int	init_time;

	*philosophers = (t_philosopher *)malloc(symposium->assistants
			* sizeof(t_philosopher));
	// need to free sympos
	if (!*philosophers)
		exit(EXIT_FAILURE);
	*philo_threads = (pthread_t *)malloc(symposium->assistants
			* sizeof(pthread_t));
	// need to free sympos & philosophers
	if (!*philo_threads)
		exit(EXIT_FAILURE);
	init_time = get_act_time();
	fill_philos(symposium, *philosophers, init_time);
	run_philos(symposium->assistants, *philosophers, *philo_threads);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:45 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/09 15:38:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Liberates resources if an error ocurrs
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param philosophers Every single data for every philosopher
 * @param c Mode to know what to liberate.
 * @return Void
 */
static inline void	free_on_error(t_philo_common *common_args,
		t_philo_single **philosophers, int c)
{
	free(common_args->forks);
	if (c == 1)
	{
		free(*philosophers);
		write(2, "Error allocating the memory needed for philo threads\n", 53);
	}
	else
		write(2, "Error allocating the memory needed for philostructs\n", 52);
	exit(EXIT_FAILURE);
}

/**
 * @brief Assign all data needed by every single philosopher
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param philosophers Every single data for every philosopher
 * @return Void
 */
static inline void	fill_philos(t_philo_common *common_args,
		t_philo_single *philosophers)
{
	int	i;

	i = 0;
	while (i < common_args->assistants)
	{
		philosophers[i].id = i;
		philosophers[i].id_left = ((i + 1) % common_args->assistants);
		philosophers[i].init_time = get_act_time();
		philosophers[i].last_meal_time = philosophers[i].init_time;
		philosophers[i].eat_n_times = common_args->eat_n_times;
		philosophers[i].alive = 1;
		pthread_mutex_init(&(philosophers[i].check_if_alive), NULL);
		pthread_mutex_init(&(philosophers[i].check_last_meal), NULL);
		pthread_mutex_init(&(philosophers[i].check_n_meals), NULL);
		philosophers[i].common_args = common_args;
		i++;
	}
}

/**
 * @brief Launches n threads one per philosopher
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param philosophers Every single data for every philosopher
 * @param philo_threads Every thread that is going to be launched
 * @return Void
 */
static inline void	run_philos(t_philo_common *common_args,
		t_philo_single *philosophers, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	common_args->epoch = get_act_time();
	while (i < common_args->assistants)
	{
		if ((i % 2) == 0)
			usleep((common_args->time_to_die * 1000) / 20);
		pthread_create(&(philo_threads[i]), NULL, philo_life,
			&(philosophers[i]));
		i++;
	}
}

void	create_philos(t_philo_common *common_args,
		t_philo_single **philosophers, pthread_t **philo_threads)
{
	*philosophers = (t_philo_single *)malloc(common_args->assistants
			* sizeof(t_philo_single));
	if (!*philosophers)
		free_on_error(common_args, philosophers, 0);
	*philo_threads = (pthread_t *)malloc(common_args->assistants
			* sizeof(pthread_t));
	if (!*philo_threads)
		free_on_error(common_args, philosophers, 1);
	fill_philos(common_args, *philosophers);
	run_philos(common_args, *philosophers, *philo_threads);
}

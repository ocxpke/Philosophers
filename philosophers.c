/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:38 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:22:39 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	free_philo(t_symposium symposium,
		t_philosopher *philosopher, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < symposium.assistants)
	{
		pthread_mutex_destroy(&(philosopher[i].check_status));
		pthread_mutex_destroy(&(philosopher[i].check_if_dead));
		pthread_mutex_destroy(&(symposium.forks[i]));
		i++;
	}
	pthread_mutex_destroy(&symposium.get_time);
	pthread_mutex_destroy(&symposium.kylix);
	free(symposium.forks);
	free(philosopher);
	free(philo_threads);
}

int	main(int argc, char **argv)
{
	t_symposium		symposium;
	t_philosopher	*philosophers;
	pthread_t		*philo_threads;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "Error, not enough arguments\n", 28), 1);
	start_philo_t(argc, argv, &symposium);
	create_philos(&symposium, &philosophers, &philo_threads);
	launch_philo_monitor(philosophers);
	while (i < symposium.assistants)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	free_philo(symposium, philosophers, philo_threads);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:38 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/15 21:42:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	free_philo(t_symposium symposium,
		t_philosopher *philosopher, pthread_t *philo_threads)
{
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
		return (write(2, "Error\n", 6), 1);
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

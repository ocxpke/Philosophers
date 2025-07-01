/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:38 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/01 17:45:33 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	free_philo(t_philo_common common_args,
		t_philo_single *philosopher, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < common_args.assistants)
	{
		pthread_mutex_destroy(&(philosopher[i].check_if_alive));
		pthread_mutex_destroy(&(philosopher[i].check_last_meal));
		pthread_mutex_destroy(&(philosopher[i].check_n_meals));
		pthread_mutex_destroy(&(common_args.forks[i]));
		i++;
	}
	pthread_mutex_destroy(&common_args.kylix);
	free(common_args.forks);
	free(philosopher);
	free(philo_threads);
}

int	main(int argc, char **argv)
{
	t_philo_common	common_args;
	t_philo_single	*philosophers;
	pthread_t		*philo_threads;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18), EXIT_FAILURE);
	start_philo_t(argc, argv, &common_args);
	create_philos(&common_args, &philosophers, &philo_threads);
	launch_philo_monitor(philosophers);
	while (i < common_args.assistants)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	free_philo(common_args, philosophers, philo_threads);
}

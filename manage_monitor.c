/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:33:19 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/15 22:09:19 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_philos_alive(void *philos)
{
	t_philosopher	*all_philos;
	int				cont;
	int				i;

	all_philos = (t_philosopher *)philos;
	cont = 1;
	while (cont)
	{
		i = 0;
		while (i < all_philos[0].assistants)
		{
			if (!all_philos[i].alive || !all_philos[i].eat_n_times)
				cont = 0;
			i++;
		}
		usleep(1000);
	}
	i = 0;
	while (i < all_philos[0].assistants)
	{
		all_philos[i].exec = 0;
		i++;
	}
	return (NULL);
}

void	launch_philo_monitor(t_philosopher *philosophers)
{
	pthread_t	philo_monitor;

	pthread_create(&philo_monitor, NULL, check_philos_alive, philosophers);
	pthread_detach(philo_monitor);
}

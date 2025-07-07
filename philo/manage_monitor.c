/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:33:19 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 14:41:13 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks if philo died or has eaten n times
 *
 * @param all_philos All philosophers
 * @return Void
 */
static inline int	all_ended_eating(t_philo_single *all_philos)
{
	int	ret;
	int	i;

	pthread_mutex_lock(&(all_philos[0].check_n_meals));
	if (all_philos[0].eat_n_times == -1)
	{
		pthread_mutex_unlock(&(all_philos[0].check_n_meals));
		return (1);
	}
	pthread_mutex_unlock(&(all_philos[0].check_n_meals));
	i = 0;
	ret = 0;
	while (i < all_philos[0].common_args->assistants)
	{
		pthread_mutex_lock(&(all_philos[i].check_n_meals));
		if (all_philos[i].eat_n_times > 0)
			ret = 1;
		pthread_mutex_unlock(&(all_philos[i].check_n_meals));
		i++;
	}
	return (ret);
}

/**
 * @brief Checks if philo died or has eaten n times
 *
 * @param philos All data needed by single philo
 * @param loop Continue/Stops the life cycle
 * @return Void
 */
static inline void	check_philos_status(t_philo_single *all_philos, int *loop)
{
	int	time_passed;
	int	i;
	int	jump;

	i = 0;
	*loop = all_ended_eating(all_philos);
	while ((i < all_philos[0].common_args->assistants) && (*loop))
	{
		jump = 0;
		pthread_mutex_lock(&(all_philos[i].check_n_meals));
		if (all_philos[i].eat_n_times == 0)
			jump = 1;
		pthread_mutex_unlock(&(all_philos[i].check_n_meals));
		if (!jump)
		{
			pthread_mutex_lock(&(all_philos[i].check_last_meal));
			time_passed = (get_act_time() - all_philos[i].last_meal_time);
			pthread_mutex_unlock(&(all_philos[i].check_last_meal));
			if (time_passed > all_philos[i].common_args->time_to_die)
				someone_has_died(all_philos, loop, i);
		}
		i++;
	}
	usleep(1000);
}

/**
 * @brief Kills all the running threads
 *
 * @param all_philos All data needed by single philo
 * @return Void
 */
static inline void	stop_running_philos(t_philo_single *all_philos)
{
	int	i;

	i = 0;
	while (i < all_philos[0].common_args->assistants)
	{
		pthread_mutex_lock(&(all_philos[i].check_if_alive));
		all_philos[i].alive = 0;
		pthread_mutex_unlock(&(all_philos[i].check_if_alive));
		i++;
	}
}

/**
 * @brief Life cycle of philo_thread
 *
 * @param philos All data needed by single philo
 * @return Always NULL
 */
static void	*monitoring_philos(void *philos)
{
	t_philo_single	*all_philos;
	int				loop;

	all_philos = (t_philo_single *)philos;
	loop = 1;
	while (loop)
		check_philos_status(philos, &loop);
	stop_running_philos(all_philos);
	return (NULL);
}

void	launch_philo_monitor(t_philo_single *philosophers)
{
	pthread_t	philo_monitor;

	pthread_create(&philo_monitor, NULL, monitoring_philos, philosophers);
	pthread_join(philo_monitor, NULL);
}

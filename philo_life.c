/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/16 20:53:48 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline int	exec_time(t_philosopher *philo)
{
	return (get_act_time() - philo->init_time);
}

static inline void	philo_says(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&(philo->check_status));
	if (philo->exec)
	{
		pthread_mutex_lock(&philo->kylix);
		printf("[%d] %d %s\n", exec_time(philo), philo->id + 1, message);
		pthread_mutex_unlock(&philo->kylix);
	}
	pthread_mutex_unlock(&(philo->check_status));
}

void	philo_meal(t_philosopher *philo)
{
	int	first_to_take;
	int	second_to_take;

	first_to_take = philo->id;
	second_to_take = philo->id_left;
	if ((philo->id % 2) != 0)
	{
		first_to_take = philo->id_left;
		second_to_take = philo->id;
	}
	pthread_mutex_lock(&(philo->forks[first_to_take]));
	philo_says(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->forks[second_to_take]));
	philo_says(philo, "has taken a fork");
	philo_says(philo, "is eating");
	philo->last_meal_time = get_act_time() - philo->last_meal_time;
	usleep(philo->time_to_eat * 1000);
	philo->last_meal_time = get_act_time();
	pthread_mutex_unlock(&(philo->forks[first_to_take]));
	pthread_mutex_unlock(&(philo->forks[second_to_take]));
	if (philo->eat_n_times > 0)
		philo->eat_n_times--;
}

void	*philo_life(void *philo_info)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_info;
	philo->last_meal_time = get_act_time();
	pthread_mutex_lock(&(philo->check_status));
	while (philo->exec && (philo->eat_n_times != 0))
	{
		pthread_mutex_unlock(&(philo->check_status));
		philo_says(philo, "is thinking");
		philo_meal(philo);
		philo_says(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		pthread_mutex_lock(&(philo->check_status));
	}
	pthread_mutex_unlock(&(philo->check_status));
	return (NULL);
}

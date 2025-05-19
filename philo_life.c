/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:23:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline int	exec_time(t_philosopher *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->get_time);
	ret = get_act_time() - philo->init_time;
	pthread_mutex_unlock(&philo->get_time);
	return (ret);
}

static inline void	philo_says(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&(philo->check_status));
	if (philo->exec)
	{
		pthread_mutex_unlock(&(philo->check_status));
		pthread_mutex_lock(&philo->kylix);
		printf("[%d] %d %s\n", exec_time(philo), philo->id + 1, message);
		pthread_mutex_unlock(&philo->kylix);
	}
	else
		pthread_mutex_unlock(&(philo->check_status));
}

void	philo_meal(t_philosopher *philo)
{
	int	first_to_take;
	int	second_to_take;

	assing_order_forks(philo, &first_to_take, &second_to_take);
	pthread_mutex_lock(&(philo->forks[first_to_take]));
	philo_says(philo, "has taken a fork");
	if (philo->id == philo->id_left)
		return (wait_till_dead(philo));
	pthread_mutex_lock(&(philo->forks[second_to_take]));
	philo_says(philo, "has taken a fork");
	philo_says(philo, "is eating");
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_lock(&(philo->check_if_dead));
	philo->last_meal_time = get_act_time();
	pthread_mutex_unlock(&(philo->check_if_dead));
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
		ft_usleep(philo, philo->time_to_sleep);
		pthread_mutex_lock(&(philo->check_status));
	}
	pthread_mutex_unlock(&(philo->check_status));
	return (NULL);
}

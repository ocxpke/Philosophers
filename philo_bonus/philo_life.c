/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:30:44 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/02 14:51:39 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static inline void	colored_print(t_philo_bonus_common *common_args,
		char *message, int id)
{
	char	*color;

	if ((id % 6) == 0)
		color = ANSI_CYAN;
	else if ((id % 6) == 1)
		color = ANSI_RED;
	else if ((id % 6) == 2)
		color = ANSI_GREEN;
	else if ((id % 6) == 3)
		color = ANSI_YELLOW;
	else if ((id % 6) == 4)
		color = ANSI_BLUE;
	else
		color = ANSI_MAGENTA;
	printf("[%d] %s%d %s%s\n", get_act_time() - common_args->epoch, color, id
		+ 1, message, ANSI_RESET);
}

static inline void	philo_says(t_philo_bonus_common *common_args, char *message,
		int id)
{
	sem_wait(common_args->kylix);
	colored_print(common_args, message, id);
	sem_post(common_args->kylix);
}

static inline void	philo_meal(t_philo_bonus_common *common_args,
		t_philo_bonus_individual *philo_stats)
{
	sem_wait(common_args->at_least_pair);
	sem_wait(common_args->sem_forks);
	philo_says(common_args, "has taken a fork", philo_stats->id);
	sem_wait(common_args->sem_forks);
	philo_says(common_args, "has taken a fork", philo_stats->id);
	sem_post(common_args->at_least_pair);
	philo_says(common_args, "is eating", philo_stats->id);
	sem_wait(philo_stats->check_last_meal);
	philo_stats->last_meal_time = get_act_time();
	sem_post(philo_stats->check_last_meal);
	ft_usleep(common_args->time_to_eat);
	sem_post(common_args->sem_forks);
	sem_post(common_args->sem_forks);
	sem_wait(philo_stats->check_n_meals);
	if (philo_stats->eat_n_times != -1)
		philo_stats->eat_n_times--;
	sem_post(philo_stats->check_n_meals);
}

int	init_philo_indi_sem(t_philo_bonus_individual *philo_stats)
{
	char	name_check_alive[20];
	char	name_check_n_meals[22];
	char	n_check_l_meal[24];

	set_names_sem_philos_indi(philo_stats, name_check_alive, name_check_n_meals,
		n_check_l_meal);
	philo_stats->check_alive = sem_open(name_check_alive, O_CREAT, 0660, 1);
	if (!philo_stats->check_alive)
		return (1);
	sem_unlink(name_check_alive);
	philo_stats->check_n_meals = sem_open(name_check_n_meals, O_CREAT, 0660, 1);
	if (!philo_stats->check_n_meals)
		return (sem_close(philo_stats->check_alive), 1);
	sem_unlink(name_check_n_meals);
	philo_stats->check_last_meal = sem_open(n_check_l_meal, O_CREAT, 0660, 1);
	if (!philo_stats->check_last_meal)
		return (sem_close(philo_stats->check_alive),
			sem_close(philo_stats->check_n_meals), 1);
	sem_unlink(n_check_l_meal);
	return (0);
}

void	philo_life(t_philo_bonus_common *common_args, int id)
{
	t_philo_bonus_individual	philo_stats;

	init_philo_struct(common_args, &philo_stats, id);
	sem_wait(philo_stats.check_alive);
	sem_wait(philo_stats.check_n_meals);
	while (philo_stats.alive && (philo_stats.eat_n_times != 0))
	{
		sem_post(philo_stats.check_alive);
		sem_post(philo_stats.check_n_meals);
		philo_says(common_args, "is thinking", philo_stats.id);
		philo_meal(common_args, &philo_stats);
		philo_says(common_args, "is sleeping", philo_stats.id);
		ft_usleep(common_args->time_to_sleep);
		sem_wait(philo_stats.check_alive);
		sem_wait(philo_stats.check_n_meals);
	}
	sem_post(philo_stats.check_alive);
	sem_post(philo_stats.check_n_meals);
	sem_close(philo_stats.check_alive);
	sem_close(philo_stats.check_n_meals);
	sem_close(philo_stats.check_last_meal);
}

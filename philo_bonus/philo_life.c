/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:30:44 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/04 15:56:10 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static inline void	colored_print(t_philo_bonus_individual *philo_stats,
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
	printf("[%d] %s%d %s%s\n", get_act_time() - philo_stats->common_args->epoch,
		color, id + 1, message, ANSI_RESET);
}

inline void	philo_says(t_philo_bonus_individual *philo_stats, char *message,
		int id)
{
	int	ret;

	sem_wait(philo_stats->check_alive);
	ret = philo_stats->alive;
	sem_post(philo_stats->check_alive);
	if (!ret)
		return ;
	sem_wait(philo_stats->common_args->kylix);
	colored_print(philo_stats, message, id);
	sem_post(philo_stats->common_args->kylix);
}

inline void	philo_meal(t_philo_bonus_individual *philo_stats)
{
	sem_wait(philo_stats->common_args->at_least_pair);
	sem_wait(philo_stats->common_args->sem_forks);
	philo_says(philo_stats, "has taken a fork", philo_stats->id);
	if (philo_stats->common_args->assistants == 1)
		return (sem_post(philo_stats->common_args->sem_forks),
			sem_post(philo_stats->common_args->sem_forks),
			ft_usleep(philo_stats, philo_stats->common_args->time_to_die + 1000));
	sem_wait(philo_stats->common_args->sem_forks);
	philo_says(philo_stats, "has taken a fork", philo_stats->id);
	sem_post(philo_stats->common_args->at_least_pair);
	philo_says(philo_stats, "is eating", philo_stats->id);
	sem_wait(philo_stats->check_last_meal);
	philo_stats->last_meal_time = get_act_time();
	sem_post(philo_stats->check_last_meal);
	ft_usleep(philo_stats, philo_stats->common_args->time_to_eat);
	sem_post(philo_stats->common_args->sem_forks);
	sem_post(philo_stats->common_args->sem_forks);
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

	set_names_sem_philos_indi(name_check_alive, name_check_n_meals,
		n_check_l_meal, philo_stats);
	philo_stats->check_alive = sem_open(name_check_alive, O_CREAT, 0660, 1);
	if (!philo_stats->check_alive)
		return (1);
	sem_unlink(name_check_alive);
	philo_stats->check_n_meals = sem_open(name_check_n_meals, O_CREAT, 0660, 1);
	if (!philo_stats->check_n_meals)
		return (1);
	sem_unlink(name_check_n_meals);
	philo_stats->check_last_meal = sem_open(n_check_l_meal, O_CREAT, 0660, 1);
	if (!philo_stats->check_last_meal)
		return (sem_close(philo_stats->check_n_meals), 1);
	sem_unlink(n_check_l_meal);
	return (0);
}

void	philo_life(t_philo_bonus_common *common_args, int id)
{
	t_philo_bonus_individual	philo_stats;
	pthread_t					monitor;
	pthread_t					reaper;

	init_philo_struct(common_args, &philo_stats, id);
	launch_philo_monitor(&monitor, &philo_stats);
	launch_reaper(&reaper, &philo_stats);
	sem_wait(philo_stats.check_alive);
	sem_wait(philo_stats.check_n_meals);
	while (philo_stats.alive && (philo_stats.eat_n_times != 0))
		philo_routine(&philo_stats);
	sem_post(philo_stats.check_alive);
	sem_post(philo_stats.check_n_meals);
	pthread_join(monitor, NULL);
	pthread_join(reaper, NULL);
	sem_close(philo_stats.check_n_meals);
	sem_close(philo_stats.check_last_meal);
	sem_close(philo_stats.check_alive);
}

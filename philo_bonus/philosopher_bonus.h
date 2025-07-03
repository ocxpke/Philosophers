/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:43:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/03 20:37:45 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include "../philo/colors.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo_bonus_common
{
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						eat_n_times;
	int						assistants;
	int						epoch;
	int						someone_dead;
	sem_t					*kylix;
	sem_t					*sem_forks;
	sem_t					*at_least_pair;
	sem_t					*check_someone_died;
}							t_philo_bonus_common;

typedef struct s_philo_bonus_individual
{
	int						id;
	int						last_meal_time;
	int						eat_n_times;
	sem_t					*check_last_meal;
	sem_t					*check_n_meals;
	t_philo_bonus_common	*common_args;
}							t_philo_bonus_individual;

int							get_act_time(void);
void						start_philo_bonus_common_t(int argc, char **argv,
								t_philo_bonus_common *common_args);
long long int				ft_latoi(const char *nptr);
int							ft_isdigit(int c);
int							ft_strlen(char *arg);
void						ft_bzero(void *s, size_t n);
size_t						ft_strlcat(char *dst, const char *src, size_t size);

void						start_philo_bonus_individual_t(pid_t **all_pids,
								t_philo_bonus_common *common_args);
void						free_philo_bonus(t_philo_bonus_common *common_args,
								pid_t **all_pids);
void						ft_usleep(int time);
char						*ft_itoa(int n);

void						set_names_sem_philos_indi(char *name_check_n_meals,
								char *name_check_last_meal,
								t_philo_bonus_individual *philo_stats);

void						philo_life(t_philo_bonus_common *common_args,
								int id);

void						init_philo_struct(t_philo_bonus_common *common_args,
								t_philo_bonus_individual *philo_stats, int id);
int							init_philo_indi_sem(t_philo_bonus_individual *p_st);

void						launch_philo_monitor(pthread_t *monitor,
								t_philo_bonus_individual *philo_stats);
#endif

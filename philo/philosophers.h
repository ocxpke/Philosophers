/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 14:50:12 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "colors.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_common
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	kylix;
	pthread_mutex_t	someone_died;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_n_times;
	int				assistants;
	int				epoch;
	int				someone_dead;
}					t_philo_common;

typedef struct s_philo_single
{
	int				id;
	int				id_left;
	int				init_time;
	int				last_meal_time;
	int				eat_n_times;
	int				alive;
	pthread_mutex_t	check_if_alive;
	pthread_mutex_t	check_last_meal;
	pthread_mutex_t	check_n_meals;
	t_philo_common	*common_args;
}					t_philo_single;

/**		________________________________
 *		|
 *		|	PHILO_AUX.C FILE
 *		|_______________________________
 */

/**
 * @brief Transformrs the ascii recived to integer
 *
 * @param nptr Pointer to the string where the number is
 * @return The long long integer value
 */
long long int		ft_latoi(const char *nptr);

/**
 * @brief Returns if c is a numeric digit character or not
 *
 * @param c The ascii value of the character
 * @return If it is a numeric digit character or not
 */
int					ft_isdigit(int c);

/**
 * @brief Gives you the length of s
 *
 * @param arg String we will measure
 * @return Size of s
 */
int					ft_strlen(char *arg);

/**		________________________________
 *		|
 *		|	MANAGE_ARGS.C FILE
 *		|_______________________________
 */

/**
 * @brief Analize all the args received, and initialize the common structure
 *
 * @param argc Number of items user passed as arguments.
 * @param argv All data received by user.
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @return Void
 */
void				start_philo_t(int argc, char **argv,
						t_philo_common *common_args);

/**		________________________________
 *		|
 *		|	MANAGE_PHILOSOPHERS.C FILE
 *		|_______________________________
 */

/**
 * @brief Here we allocate all the necesary memory, filled with the philo data
 * and threads are launched
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param philosophers Every single data for every philosopher
 * @param philo_threads Every thread that is going to be launched
 * @return Void
 */
void				create_philos(t_philo_common *common_args,
						t_philo_single **philosophers,
						pthread_t **philo_threads);

/**		________________________________
 *		|
 *		|	FT_USLEEP.C FILE
 *		|_______________________________
 */

/**
 * @brief Waits n_time and checks if philo is dead between waits
 *
 * @param philo Individual data from every philosopher
 * @param time_to_wait Time to be waited
 * @return Void
 */
void				ft_usleep(t_philo_single *philo, int time_to_wait);

/**		________________________________
 *		|
 *		|	MANAGE_TIME.C FILE
 *		|_______________________________
 */

/**
 * @brief Gets the current actual time since epoch.
 *
 * @return The current actual time since epoch (Linux).
 */
int					get_act_time(void);

/**		________________________________
 *		|
 *		|	PHILO_LIFE.C FILE
 *		|_______________________________
 */

/**
 * @brief Proccess that will be executed by philo,
 * here creates 2 threads monitor and reaper. Also executes the philo routine.
 *
 * @param philo_info All data needed by the philosopher
 * @return Always NULL.
 */
void				*philo_life(void *philo_info);

/**		________________________________
 *		|
 *		|	PHILO_LIFE_AUX.C FILE
 *		|_______________________________
 */

/**
 * @brief Assign the order of the philo for taking forks, with this method
 * we avoid deadlocks
 *
 * @param philo All data needed by a single philosopher
 * @param first_to_take First fork pos to be taken
 * @param second_to_take Second fork pos to be taken
 * @return Void.
 */
void				assign_order_forks(t_philo_single *philo,
						int *first_to_take, int *second_to_take);

/**
 * @brief In case of only 1  philo he takes one frok and waits till he dies
 *
 * @param philo All data needed by a single philosopher
 * @return Void.
 */
void				wait_till_dead(t_philo_single *philo);

/**		________________________________
 *		|
 *		|	MANAGE_MONITOR.C FILE
 *		|_______________________________
 */

/**
 * @brief Launches the monitor that checks if philo died of starvation
 * or has ate n meals
 *
 * @param philo All data needed by a single philosopher
 * @return Void.
 */
void				launch_philo_monitor(t_philo_single *philosophers);

/**		________________________________
 *		|
 *		|	MONITOR_AUX.C FILE
 *		|_______________________________
 */

/**
 * @brief In case of only 1  philo he takes one frok and waits till he dies
 *
 * @param philo All data needed by a single philosopher
 * @return Void.
 */
void				someone_has_died(t_philo_single *all_philos, int *loop,
						int i);

#endif

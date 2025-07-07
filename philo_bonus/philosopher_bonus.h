/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:43:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 13:54:16 by jose-ara         ###   ########.fr       */
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
	sem_t					*kylix;
	sem_t					*sem_forks;
	sem_t					*at_least_pair;
	sem_t					*death;
	sem_t					*n_meals;
	sem_t					**destroyer_of_worlds;
}							t_philo_bonus_common;

typedef struct s_philo_bonus_individual
{
	int						id;
	int						last_meal_time;
	int						eat_n_times;
	int						alive;
	sem_t					*check_last_meal;
	sem_t					*check_alive;
	sem_t					*check_n_meals;
	t_philo_bonus_common	*common_args;
}							t_philo_bonus_individual;

/**		________________________________
 *		|
 *		|	PHILOSOPHERS_BONUS.C FILE
 *		|_______________________________
 */

/**
 * @brief Liberates all the resourcers that are common between philosophers
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param all_pids Array of all pid_t from all process created.
 * @return Void.
 */
void						free_philo_bonus(t_philo_bonus_common *common_args,
								pid_t **all_pids);

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
int							get_act_time(void);

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
void						start_philo_bonus_common_t(int argc, char **argv,
								t_philo_bonus_common *common_args);

/**		________________________________
 *		|
 *		|	MANAGE_ARGS_AUX.C FILE
 *		|_______________________________
 */

/**
 * @brief Casts the philosopher ID to char * to be used at
 * the semaphores /destroyer_of_worlds
 *
 * @param id Id number of the philosopher
 * @return The id of the philosophers passed as a string.
 */
char						*get_destroyer_name(int id);

/**		________________________________
 *		|
 *		|	MANAGE_PHILOS.C FILE
 *		|_______________________________
 */

/**
 * @brief Creates a process for every philos and ends them in a correct way.
 * Also generates the array of pid_t
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param all_pids Array of all pid_t from all process created.
 * @return Void.
 */
void						start_philo_bonus_individual_t(pid_t **all_pids,
								t_philo_bonus_common *common_args);

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
long long int				ft_latoi(const char *nptr);

/**
 * @brief Returns if c is a numeric digit character or not
 *
 * @param c The ascii value of the character
 * @return If it is a numeric digit character or not
 */
int							ft_isdigit(int c);

/**
 * @brief Gives you the length of s
 *
 * @param arg String we will measure
 * @return Size of s
 */
int							ft_strlen(char *arg);

/**
 * @brief Set first n-positions to 0
 *
 * @param s Void pointer
 * @param n Number of bytes to check
 * @return Void
 */
void						ft_bzero(void *s, size_t n);

/**
 * @brief Concatenates dst and src in the buffer of length size
 *
 * @param dst First string
 * @param src Second string
 * @param size Total lentgh of buffer
 * @return Size of the string that tried to/has create
 */
size_t						ft_strlcat(char *dst, const char *src, size_t size);

/**		________________________________
 *		|
 *		|	FT_USLEEP.C FILE
 *		|_______________________________
 */

/**
 * @brief Waits n_time and checks if philo is dead between waits
 *
 * @param philo_stats Individual data from every philosopher
 * @param time Time to be waited
 * @return Void
 */
void						ft_usleep(t_philo_bonus_individual *philo_stats,
								int time);

/**		________________________________
 *		|
 *		|	FT_ITOA.C FILE
 *		|_______________________________
 */

/**
 * @brief Takes an unsigned integer and casts it to ascii
 *
 * @param n Number to cast to ascii
 * @return Pointer to positon of the new string or null
 */
char						*ft_itoa(int n);

/**		________________________________
 *		|
 *		|	PHILO_LIFE.C FILE
 *		|_______________________________
 */

/**
 * @brief Philo says [message] printed with an associated color and
 * waiting for the semaphorters required
 *
 * @param philo_stats Individual data from every philosopher
 * @param message Message to be printed by philosopher.
 * @param id The ID of the philosopher.
 * @return Void
 */
void						philo_says(t_philo_bonus_individual *philo_stats,
								char *message, int id);
/**
 * @brief Steps to be done by the philosopher to eat.
 * (Sem waits and post & checking dead status and n_meals)
 *
 * @param philo_stats Individual data from every philosopher
 * @return Void
 */
void						philo_meal(t_philo_bonus_individual *philo_stats);

/**
 * @brief Creates all the semaphores required by single philo.
 *
 * @param p_st Individual data from every philosopher
 * @return 0 if all OK, 1 if something went wrong.
 */
int							init_philo_indi_sem(t_philo_bonus_individual *p_st);

/**
 * @brief Proccess that will be executed by philo,
 * here creates 2 threads monitor and reaper. Also executes the philo routine.
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param id ID of the philosopher
 * @return Void.
 */
void						philo_life(t_philo_bonus_common *common_args,
								int id);

/**		________________________________
 *		|
 *		|	PHILO_LIFE_AUX.C FILE
 *		|_______________________________
 */

/**
 * @brief Initialize the philo single structure
 *
 * @param name_check_alive Name of the semaphore for check if philo
 * is alive
 * @param name_check_n_meals Name of the semaphore for check the number
 * of meals
 * @param name_check_last_meal Name of the semaphore for check the last
 * meal time
 * @param philo_stats Individual data from every philosopher
 * @return Void
 */
void						set_names_sem_philos_indi(char *name_check_alive,
								char *name_check_n_meals,
								char *name_check_last_meal,
								t_philo_bonus_individual *philo_stats);

/**
 * @brief Initialize the philo single structure
 *
 * @param commong_args Args shared by all philosophers
 * @param philo_stats Individual data from every philosopher
 * @param id The philosopher ID
 * @return Void
 */
void						init_philo_struct(t_philo_bonus_common *common_args,
								t_philo_bonus_individual *philo_stats, int id);

/**
 * @brief Basic philosopher life cycle
 *
 * @param p_st Individual data from every philosopher
 * @return Void
 */
void						philo_routine(t_philo_bonus_individual *p_st);

/**		________________________________
 *		|
 *		|	MANAGE_MONITOR.C FILE
 *		|_______________________________
 */

/**
 * @brief Launchs the monitor thread that is encharged of
 * checking the n_meals and last_time meal
 *
 * @param monitor Thread to be launch
 * @param philo_stats Individual data from every philosopher
 * @return Void
 */
void						launch_philo_monitor(pthread_t *monitor,
								t_philo_bonus_individual *philo_stats);

/**		________________________________
 *		|
 *		|	MANAGE_REAPER.C FILE
 *		|_______________________________
 */

/**
 * @brief Launchs the reaper thread that is encharged of
 * manages of philo needs to die
 *
 * @param reaper Thread to be launch
 * @param philo_stats Individual data from every philosopher
 * @return Void
 */
void						launch_reaper(pthread_t *reaper,
								t_philo_bonus_individual *philo_stats);

/**		________________________________
 *		|
 *		|	MAIN_MONITORS.C FILE
 *		|_______________________________
 */

void						launch_main_monitors(pthread_t *monitor_death,
								pthread_t *monitor_meals,
								t_philo_bonus_common *common_args);

/**		________________________________
 *		|
 *		|	CLOSE_HELPER.C FILE
 *		|_______________________________
 */

/**
 * @brief Liberates all semapphores by closeing them,
 * we call this due to an error
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @param mode Flag used to check what to be freed
 * @return Void.
 */
void						close_aux(t_philo_bonus_common *common_args,
								int mode);
#endif

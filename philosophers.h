/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/19 20:21:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	kylix;
	pthread_mutex_t	get_time;
	pthread_mutex_t	check_status;
	pthread_mutex_t	check_if_dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				init_time;
	int				last_meal_time;
	int				eat_n_times;
	int				id;
	int				id_left;
	int				exec;
	int				assistants;
}					t_philosopher;

typedef struct s_symposium
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	kylix;
	pthread_mutex_t	get_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_n_times;
	int				assistants;
}					t_symposium;

void				start_philo_t(int argc, char **argv,
						t_symposium *symposium);

void				create_philos(t_symposium *symposium,
						t_philosopher **philosophers,
						pthread_t **philo_threads);

void				*philo_life(void *philo_info);

int					get_act_time(void);

int					exec_time(t_philosopher *philo);

void				launch_philo_monitor(t_philosopher *philosophers);

int					ft_atoi(const char *nptr);

void				ft_usleep(t_philosopher *philo, int time_to_wait);

void				assing_order_forks(t_philosopher *philo, int *first_to_take,
						int *second_to_take);

void				wait_till_dead(t_philosopher *philo);

#endif

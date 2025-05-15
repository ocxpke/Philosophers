/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/15 21:53:49 by jose-ara         ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				init_time;
	int				last_meal_time;
	int				eat_n_times;
	int				id;
	int				id_left;
	int				alive;
	int				exec;
	int				assistants;
}					t_philosopher;

typedef struct s_symposium
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	kylix;
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

void				launch_philo_monitor(t_philosopher *philosophers);

int					ft_atoi(const char *nptr);

#endif

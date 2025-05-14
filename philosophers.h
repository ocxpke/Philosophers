/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 21:09:21 by jose-ara         ###   ########.fr       */
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

typedef struct eat_stack
{
	int					philo_id;
	struct eat_stack	*philo_next;
}						t_eat_stack;

typedef struct s_philosopher
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		kylix;
	__useconds_t		time_to_die;
	__useconds_t		time_to_eat;
	__useconds_t		time_to_sleep;
	int					eat_n_times;
	int					id;
	int					id_left;
	t_eat_stack			**eat_stack;
}						t_philosopher;

typedef struct s_symposium
{
	pthread_t			*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		kylix;
	__useconds_t		time_to_die;
	__useconds_t		time_to_eat;
	__useconds_t		time_to_sleep;
	int					eat_n_times;
	int					assitants;
	t_eat_stack			*eat_stack;
}						t_symposium;

void					start_philo_t(int argc, char **argv,
							t_symposium *symposium);

void					create_philos(t_symposium *symposium,
							t_philosopher **philosophers,
							pthread_t **philo_threads);

t_eat_stack				*init_eat_stack(int assistants);

void					*philo_life(void *philo_info);

int						get_act_time(void);

int						ft_atoi(const char *nptr);

#endif

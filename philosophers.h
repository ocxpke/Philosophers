/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:58:59 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/08 21:40:16 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct meal_queue
{
	t_philosopher	philo;
	t_philosopher	*next;
};

typedef struct s_philosopher
{
	int				id;
	pthread_t		philo;
	__useconds_t	time_starving;
	int				times_eaten;
}					t_philosopher;

typedef struct s_symposium
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	kylix;
	__useconds_t	time_to_die;
	__useconds_t	time_to_eat;
	__useconds_t	time_to_sleep;
	int				eat_n_times;
	int				assitants;
}					t_symposium;

int					ft_atoi(const char *nptr);

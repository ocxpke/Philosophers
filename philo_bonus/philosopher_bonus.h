/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:43:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/01 19:55:44 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include "../philo/colors.h"
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_bonus_common
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_n_times;
	int		assistants;
	int		epoch;
	sem_t	*sem_forks;
	sem_t	*at_least_pair;
}			t_philo_bonus_common;

int			get_act_time(void);
void		start_philo_bonus_t(int argc, char **argv,
				t_philo_bonus_common *common_args);

#endif

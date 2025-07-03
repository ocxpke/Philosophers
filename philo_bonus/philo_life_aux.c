/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:45:31 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/03 20:58:52 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	set_names_sem_philos_indi(char *name_check_n_meals,
		char *name_check_last_meal, t_philo_bonus_individual *philo_stats)
{
	char	*str_id;

	str_id = ft_itoa(philo_stats->id);
	ft_bzero((void *)name_check_n_meals, 20);
	ft_bzero((void *)name_check_last_meal, 20);
	ft_strlcat(name_check_n_meals, "/philo_sem_n_meals_",
		ft_strlen("/philo_sem_n_meals_"));
	ft_strlcat(name_check_n_meals, str_id, ft_strlen(str_id));
	ft_strlcat(name_check_last_meal, "/philo_sem_last_meal_",
		ft_strlen("/philo_sem_last_meal_"));
	ft_strlcat(name_check_last_meal, str_id, ft_strlen(str_id));
	free(str_id);
}

void	init_philo_struct(t_philo_bonus_common *common_args,
		t_philo_bonus_individual *philo_stats, int id)
{
	philo_stats->id = id;
	if (init_philo_indi_sem(philo_stats) == 1)
		return ;
	philo_stats->last_meal_time = get_act_time();
	philo_stats->eat_n_times = common_args->eat_n_times;
	philo_stats->common_args = common_args;
}

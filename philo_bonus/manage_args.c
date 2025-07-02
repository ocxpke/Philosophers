/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/02 11:13:50 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static inline int	check_all_num(char *arg)
{
	int	ret;
	int	i;

	if (!arg)
		return (0);
	ret = 1;
	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	while ((i < ft_strlen(arg)) && ret)
	{
		if (!ft_isdigit(arg[i]))
			ret = 0;
		i++;
	}
	return (ret);
}

static int	get_num(char *arg)
{
	long long	ret;

	if ((ft_strlen(arg) > 11) || !check_all_num(arg))
		return (-1);
	ret = ft_latoi(arg);
	if ((ret > INT_MAX) || (ret < INT_MIN))
		return (-1);
	return ((int)ret);
}

static inline void	load_init_values(int argc, char **argv,
		t_philo_bonus_common *common_args)
{
	int	aux;

	aux = get_num(argv[1]);
	if (aux <= 0)
		return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
	common_args->assistants = aux;
	aux = get_num(argv[2]);
	if (aux <= 0)
		return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
	common_args->time_to_die = aux;
	aux = get_num(argv[3]);
	if (aux <= 0)
		return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
	common_args->time_to_eat = aux;
	aux = get_num(argv[4]);
	if (aux <= 0)
		return (write(STDERR_FILENO, "Invalid args\n", 13), exit(EXIT_FAILURE));
	common_args->time_to_sleep = aux;
	if (argc == 6)
	{
		aux = get_num(argv[5]);
		if (aux <= 0)
			return (write(2, "Invalid args\n", 13), exit(EXIT_FAILURE));
		common_args->eat_n_times = aux;
	}
}

static void	create_common_semaphores(t_philo_bonus_common *common_args)
{
	common_args->sem_forks = sem_open("/forks", O_CREAT, 0660,
			common_args->assistants);
	if (!common_args->sem_forks)
		return (write(2, "Err creating sem forks\n", 23), exit(EXIT_FAILURE));
	sem_unlink("/forks");
	common_args->at_least_pair = sem_open("/pair_forks", O_CREAT, 0660, 1);
	if (!common_args->sem_forks)
		return (write(2, "Err creating pair forks\n", 24), exit(EXIT_FAILURE));
	sem_unlink("/pair_forks");
	common_args->kylix = sem_open("/kylix", O_CREAT, 0660, 1);
	if (!common_args->sem_forks)
		return (write(2, "Err creating pair forks\n", 24), exit(EXIT_FAILURE));
	sem_unlink("/kylix");
}

void	start_philo_bonus_common_t(int argc, char **argv,
		t_philo_bonus_common *common_args)
{
	common_args->eat_n_times = -1;
	load_init_values(argc, argv, common_args);
	create_common_semaphores(common_args);
}

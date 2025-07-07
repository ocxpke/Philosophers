/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 13:19:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/**
 * @brief Checks if all the characters are integers,
 * also checks if first one is a sign
 *
 * @param arg The string to be checked
 * @return 1 if it's a real number, 0 if not
 */
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

/**
 * @brief Cast the string to integer and checks if it's a real Integer value
 *
 * @param arg The string to be checked
 * @return The integer passed trhough param, or -1 if something went wrong
 */
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

/**
 * @brief Analize all the args received, and checks if args are real integers.
 * In other case ends the program.
 *
 * @param argc Number of items user passed as arguments.
 * @param argv All data received by user.
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @return Void
 */
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

/**
 * @brief Creates all the semaphores that will be used by all philosophers.
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @return Void
 */
static void	create_common_semaphores(t_philo_bonus_common *common_args)
{
	common_args->sem_forks = sem_open("/forks", O_CREAT, 0666,
			common_args->assistants);
	if (!common_args->sem_forks)
		return (write(2, "Err sem_forks\n", 14), exit(EXIT_FAILURE));
	sem_unlink("/forks");
	common_args->at_least_pair = sem_open("/pair_forks", O_CREAT, 0666, 1);
	if (!common_args->sem_forks)
		return (write(2, "Err pair_forks\n", 15), close_aux(common_args, 0));
	sem_unlink("/pair_forks");
	common_args->kylix = sem_open("/kylix", O_CREAT, 0666, 1);
	if (!common_args->sem_forks)
		return (write(2, "Err kylix\n", 10), close_aux(common_args, 1));
	sem_unlink("/kylix");
	common_args->death = sem_open("/death", O_CREAT, 0666, 0);
	if (!common_args->death)
		return (write(2, "Err death\n", 10), close_aux(common_args, 2));
	sem_unlink("/death");
	common_args->n_meals = sem_open("/n_meals", O_CREAT, 0666, 0);
	if (!common_args->n_meals)
		return (write(2, "Err n_meals\n", 12), close_aux(common_args, 3));
	sem_unlink("/n_meals");
}

void	start_philo_bonus_common_t(int argc, char **argv,
		t_philo_bonus_common *common_args)
{
	int		i;
	char	*name;

	common_args->eat_n_times = -1;
	load_init_values(argc, argv, common_args);
	create_common_semaphores(common_args);
	common_args->destroyer_of_worlds = (sem_t **)malloc(common_args->assistants
			* sizeof(sem_t *));
	if (!common_args->destroyer_of_worlds)
		return (write(2, "Err destroyer\n", 14), close_aux(common_args, 4));
	i = 0;
	while (i < common_args->assistants)
	{
		name = get_destroyer_name(i);
		common_args->destroyer_of_worlds[i] = sem_open(name, O_CREAT, 0660, 0);
		if (!common_args->destroyer_of_worlds[i])
			exit(EXIT_FAILURE);
		sem_unlink(name);
		free(name);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 14:34:08 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		t_philo_common *common_args)
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
 * @brief Creates all shraed mutex form all philos.
 *
 * @param common_args Semaphores, and basic data shared by all philosophers.
 * @return Void
 */
inline static void	create_mutexs(t_philo_common *common_args)
{
	int	i;

	i = 0;
	while (i < common_args->assistants)
	{
		pthread_mutex_init(&(common_args->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(common_args->kylix), NULL);
	pthread_mutex_init(&(common_args->someone_died), NULL);
}

void	start_philo_t(int argc, char **argv, t_philo_common *common_args)
{
	common_args->eat_n_times = -1;
	load_init_values(argc, argv, common_args);
	common_args->forks = (pthread_mutex_t *)malloc(common_args->assistants
			* sizeof(pthread_mutex_t));
	if (!common_args->forks)
		exit(EXIT_FAILURE);
	create_mutexs(common_args);
	common_args->someone_dead = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_eat_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:46:43 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 20:46:47 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_eat_stack	*init_eat_stack(int assistants)
{
	t_eat_stack	*head;
	t_eat_stack	*next;
	t_eat_stack	*aux;
	int			i;

	head = (t_eat_stack *)malloc(sizeof(t_eat_stack));
	if (!head)
		exit(EXIT_FAILURE);
	head->philo_id = 0;
	head->philo_next = NULL;
	aux = head;
	i = 1;
	while (i < assistants)
	{
		next = (t_eat_stack *)malloc(sizeof(t_eat_stack));
		if (!next)
			exit(EXIT_FAILURE);
		next->philo_id = i;
		next->philo_next = NULL;
		aux->philo_next = next;
		aux = aux->philo_next;
		i++;
	}
	return (head);
}

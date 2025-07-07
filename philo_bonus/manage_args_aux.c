/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:23:31 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/07 12:25:34 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

char	*get_destroyer_name(int id)
{
	char	*ret;
	char	*str_id;

	str_id = ft_itoa(id);
	ret = malloc(ft_strlen("/sem_destroyer_") + ft_strlen(str_id) + 1);
	if (!ret)
		return (NULL);
	ft_bzero(ret, ft_strlen("/sem_destroyer_") + ft_strlen(str_id) + 1);
	ft_strlcat(ret, "/sem_destroyer_", ft_strlen("/sem_destroyer_"));
	ft_strlcat(ret, str_id, ft_strlen(str_id));
	free(str_id);
	return (ret);
}

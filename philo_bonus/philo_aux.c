/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:54:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/02 14:32:15 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	char	*cpy;

	cpy = (char *)s;
	while (n)
	{
		(*cpy) = 0;
		cpy++;
		n--;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	i = 0;
	if (dst_len >= size)
		return (src_len + size);
	while (i < (size - dst_len - 1) && src[i])
	{
		dst[dst_len + i] = (char)src[i];
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}

int	ft_strlen(char *arg)
{
	int	ret;

	ret = 0;
	if (!arg)
		return (-1);
	while (arg[ret])
		ret++;
	return (ret);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long int	ft_latoi(const char *nptr)
{
	long long int	minus;
	long long int	number;

	number = 0;
	minus = 1;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\r'
		|| *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) && *nptr)
	{
		number = (number * 10 + ((*nptr) - '0'));
		nptr++;
	}
	return (number * minus);
}

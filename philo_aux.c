/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:54:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/14 20:46:49 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strlen(char *arg) {
  int ret = 0;
  if (!arg)
    return (-1);
  while (arg[ret])
    ret++;
  return (ret);
}

int ft_isdigit(int c) {
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

long long int ft_latoi(const char *nptr) {
  long long int minus;
  long long int number;

  number = 0;
  minus = 1;
  while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\r' ||
         *nptr == '\v' || *nptr == '\f')
    nptr++;
  if (*nptr == '+' || *nptr == '-') {
    if (*nptr == '-')
      minus = -1;
    nptr++;
  }
  while (ft_isdigit(*nptr) && *nptr) {
    number = (number * 10 + ((*nptr) - '0'));
    nptr++;
  }
  return (number * minus);
}

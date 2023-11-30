/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:48:06 by jyao              #+#    #+#             */
/*   Updated: 2022/10/14 14:34:35 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	hft_isspace(const char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

static int	hft_isngve(const char c)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			return (-1);
		return (1);
	}
	return (0);
}

int	ph_atoi(const char *str, t_philo_global *philo_g_ptr)
{
	ssize_t			num;
	int				negve;

	if (!str)
		ph_exit(philo_g_ptr);
	num = 0;
	while (hft_isspace(*str))
		str++;
	negve = hft_isngve(*str);
	if (negve)
		str++;
	if (negve < 0)
		ph_exit(philo_g_ptr);
	if (*str < '0' || *str > '9')
		ph_exit(philo_g_ptr);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (num < INT_MIN || num > INT_MAX)
		ph_exit(philo_g_ptr);
	return ((int)num);
}

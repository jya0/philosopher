/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:54:47 by jyao              #+#    #+#             */
/*   Updated: 2022/01/24 16:04:32 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static unsigned short	hft_numstrlen(int n)
{
	unsigned short	i;

	i = 0;
	if (!n || n < 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	hft_handle_negative(int *n, unsigned short *i, char *num)
{
	if (*n < 0)
	{
		*num = '-';
		if (*n == INT_MIN)
		{
			(*i)--;
			num[*i] = '8';
			*n /= 10;
		}
		*n *= -1;
	}
}

char	*philo_itoa(int n)
{
	unsigned short int	i;
	char				*num;

	i = hft_numstrlen(n);
	num = (char *)malloc((i + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[i] = '\0';
	if (!n)
		*num = '0';
	hft_handle_negative(&n, &i, num);
	while (n)
	{
		num[--i] = n % 10 + '0';
		n /= 10;
	}
	return (num);
}

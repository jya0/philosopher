/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:24:30 by jyao              #+#    #+#             */
/*   Updated: 2022/01/24 16:06:26 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	hft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*philo_strjoin(const char *s1, const char *s2)
{
	char	*sjoin;
	char	*pstart;

	sjoin = \
		(char *)malloc((hft_strlen(s1) + hft_strlen(s2) + 1) * sizeof(char));
	if (!sjoin)
		return (NULL);
	pstart = sjoin;
	while (*s1)
	{
		*sjoin = *s1;
		s1++;
		sjoin++;
	}
	while (*s2)
	{
		*sjoin = *s2;
		s2++;
		sjoin++;
	}
	*sjoin = '\0';
	return (pstart);
}

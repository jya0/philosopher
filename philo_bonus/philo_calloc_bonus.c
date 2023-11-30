/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_calloc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:51:59 by jyao              #+#    #+#             */
/*   Updated: 2022/10/14 14:34:41 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ph_calloc(size_t nitems, size_t size)
	{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(nitems * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nitems * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

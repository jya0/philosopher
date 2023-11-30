/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:51:59 by jyao              #+#    #+#             */
/*   Updated: 2022/09/15 16:53:01 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

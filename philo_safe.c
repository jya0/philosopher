/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:52:50 by jyao              #+#    #+#             */
/*   Updated: 2022/10/04 23:59:40 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_safe_value_get(t_safe *safe_ptr)
{
	int	value;

	if (!safe_ptr)
		return (-1);
	pthread_mutex_lock(&safe_ptr->mutex);
	value = safe_ptr->value;
	pthread_mutex_unlock(&safe_ptr->mutex);
	return (value);
}

void	ph_safe_value_set(t_safe *safe_ptr, int value)
{
	if (!safe_ptr)
		return ;
	pthread_mutex_lock(&safe_ptr->mutex);
	safe_ptr->value = value;
	pthread_mutex_unlock(&safe_ptr->mutex);
}

void	ph_safe_value_change(t_safe *safe_ptr, int change)
{
	if (!safe_ptr)
		return ;
	pthread_mutex_lock(&safe_ptr->mutex);
	safe_ptr->value += change;
	pthread_mutex_unlock(&safe_ptr->mutex);
}

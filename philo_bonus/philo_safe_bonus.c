/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:52:50 by jyao              #+#    #+#             */
/*   Updated: 2022/10/18 15:36:27 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

ssize_t	ph_safe_value_get(t_safe *safe_ptr)
{
	ssize_t	value;

	if (!safe_ptr)
		return (-1);
	sem_wait(safe_ptr->bin_sem);
	value = safe_ptr->value;
	sem_post(safe_ptr->bin_sem);
	return (value);
}

void	ph_safe_value_set(t_safe *safe_ptr, ssize_t value)
{
	if (!safe_ptr)
		return ;
	sem_wait(safe_ptr->bin_sem);
	safe_ptr->value = value;
	sem_post(safe_ptr->bin_sem);
}

void	ph_safe_value_change(t_safe *safe_ptr, ssize_t change)
{
	if (!safe_ptr)
		return ;
	sem_wait(safe_ptr->bin_sem);
	safe_ptr->value += change;
	sem_post(safe_ptr->bin_sem);
}

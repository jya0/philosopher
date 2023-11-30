/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_usleep_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:31:12 by jyao              #+#    #+#             */
/*   Updated: 2022/10/21 16:11:15 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_usleep(ssize_t	usec_period)
{
	ssize_t	target;

	target = ph_get_time() + usec_period;
	while (ph_get_time() < target)
		usleep(USLEEP_INTERVAL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:03:52 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 22:47:15 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*thread_is_alive(void *arg)
{
	t_philo_global	*philo_g_ptr;

	philo_g_ptr = (t_philo_global *)arg;
	while (1)
	{
		ph_act_is_dead(philo_g_ptr);
		usleep(USLEEP_INTERVAL);
	}
	return (NULL);
}

void	ph_philo_process(t_philo_global	*philo_g_ptr)
{
	t_philosopher	*philosopher;

	philosopher = philo_g_ptr->philosopher;
	ph_safe_value_set(&philosopher->s_last_ate, ph_get_time());
	pthread_create(&philosopher->th_is_alive, \
	NULL, thread_is_alive, (void *)philo_g_ptr);
	while (1)
	{
		ph_act_think(philo_g_ptr);
		ph_act_eat_sleep(philo_g_ptr, STATUS_EAT, \
		philo_g_ptr->args_main[TT_EAT] * 1000);
		ph_act_eat_sleep(philo_g_ptr, STATUS_SLEEP, \
		philo_g_ptr->args_main[TT_SLEEP] * 1000);
	}
	ph_exit(philo_g_ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus_old.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:03:52 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 19:31:49 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*thread_receiver(void	*arg)
{
	t_philo_global	*philo_g_ptr;

	philo_g_ptr = (t_philo_global *)arg;
	sem_wait(philo_g_ptr->sem_exit);
	if (ph_safe_value_get(&philo_g_ptr->philosopher->s_is_exit) == EXIT_NONE)
		ph_safe_value_set(&philo_g_ptr->philosopher->s_is_exit, EXIT_START);
	return (NULL);
}

static void	*thread_is_alive(void *arg)
{
	t_philo_global	*philo_g_ptr;

	philo_g_ptr = (t_philo_global *)arg;
	while (ph_safe_value_get(&philo_g_ptr->philosopher->s_is_exit) == EXIT_NONE)
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
	pthread_create(&philosopher->th_receiver, \
	NULL, thread_receiver, (void *)philo_g_ptr);
	pthread_create(&philosopher->th_routine, \
	NULL, thread_is_alive, (void *)philo_g_ptr);
	usleep(USLEEP_INTERVAL);
	while (ph_safe_value_get(&philo_g_ptr->philosopher->s_is_exit) == EXIT_NONE)
	{
		ph_act_think(philo_g_ptr);
		if (ph_act_eat_sleep(philo_g_ptr, STATUS_EAT, \
		philo_g_ptr->args_main[TT_EAT] * 1000) != EXIT_NONE)
			break ;
		if (ph_act_eat_sleep(philo_g_ptr, STATUS_SLEEP, \
		philo_g_ptr->args_main[TT_SLEEP] * 1000) != EXIT_NONE)
			break ;
	}
	pthread_join(philo_g_ptr->philosopher->th_receiver, NULL);
	pthread_join(philo_g_ptr->philosopher->th_routine, NULL);
	ph_exit(philo_g_ptr);
}

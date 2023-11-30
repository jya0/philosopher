/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:33:50 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 22:38:38 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ph_close_unlink_sem(sem_t *sem_ptr, const char *sem_name)
{
	if (!sem_ptr)
		return ;
	sem_close(sem_ptr);
	sem_unlink(sem_name);
}

void	ph_exit(t_philo_global	*philo_g_ptr)
{
	int	status;

	if (!philo_g_ptr)
		exit(1);
	status = 0;
	if (philo_g_ptr->philosopher)
	{
		ph_close_unlink_sem(philo_g_ptr->philosopher->s_last_ate.bin_sem, \
		philo_g_ptr->philosopher->s_last_ate.sem_name);
		free(philo_g_ptr->philosopher->s_last_ate.sem_name);
		free(philo_g_ptr->philosopher);
	}
	ph_close_unlink_sem(philo_g_ptr->sem_exit, SEM_EXIT);
	ph_close_unlink_sem(philo_g_ptr->sem_print, SEM_PRINT);
	ph_close_unlink_sem(philo_g_ptr->sem_has_to_eat, SEM_HAS_TO_EAT);
	ph_close_unlink_sem(philo_g_ptr->sem_forks, SEM_FORKS);
	free(philo_g_ptr->all_pid);
	exit(status);
}

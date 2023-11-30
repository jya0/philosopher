/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:33:50 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 18:35:56 by jyao             ###   ########.fr       */
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
		if (philo_g_ptr->philosopher->is_fork == YOINKED)
			ph_act_forks_putback(philo_g_ptr);
		status = ph_safe_value_get(&philo_g_ptr->philosopher->s_is_exit);
		ph_close_unlink_sem(philo_g_ptr->philosopher->s_is_exit.bin_sem, \
		philo_g_ptr->philosopher->s_is_exit.sem_name);
		free(philo_g_ptr->philosopher->s_is_exit.sem_name);
		ph_close_unlink_sem(philo_g_ptr->philosopher->s_last_ate.bin_sem, \
		philo_g_ptr->philosopher->s_last_ate.sem_name);
		free(philo_g_ptr->philosopher->s_last_ate.sem_name);
		free(philo_g_ptr->philosopher);
	}
	ph_close_unlink_sem(philo_g_ptr->sem_exit, "sem_exit");
	ph_close_unlink_sem(philo_g_ptr->sem_print, "sem_print");
	ph_close_unlink_sem(philo_g_ptr->sem_has_to_eat, "sem_has_to_eat");
	ph_close_unlink_sem(philo_g_ptr->sem_pair, "sem_pair");
	ph_close_unlink_sem(philo_g_ptr->sem_forks, "sem_forks");
	free(philo_g_ptr->all_pid);
	exit(status);
}

void	ph_everyone_exit(t_philo_global	*philo_g_ptr)
{
	int	i;

	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		sem_post(philo_g_ptr->sem_exit);
		i++;
	}
}

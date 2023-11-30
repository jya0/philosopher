/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:18:47 by jyao              #+#    #+#             */
/*   Updated: 2022/10/24 13:06:10 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*int value of 1 means it failed to lock the fork
**0 means it succeeded in locking the fork.
*/
void	ph_act_forks_take(t_philo_global *philo_g_ptr)
{
	sem_wait(philo_g_ptr->sem_forks);
	sem_wait(philo_g_ptr->sem_forks);
	ph_print_event(philo_g_ptr, STATUS_TAKE_FORK);
}

void	ph_act_forks_putback(t_philo_global *philo_g_ptr)
{
	sem_post(philo_g_ptr->sem_forks);
	sem_post(philo_g_ptr->sem_forks);
}

void	ph_act_think(t_philo_global *philo_g_ptr)
{
	ph_print_event(philo_g_ptr, STATUS_THINK);
	ph_act_forks_take(philo_g_ptr);
}

/*this is for sleep and eat*/
void	ph_act_eat_sleep(\
t_philo_global *philo_g_ptr, int e_status, ssize_t time_usec)
{
	ph_print_event(philo_g_ptr, e_status);
	if (e_status == STATUS_EAT)
		ph_safe_value_set(&philo_g_ptr->philosopher->s_last_ate, ph_get_time());
	ph_usleep(time_usec);
	if (e_status == STATUS_EAT)
	{
		ph_act_forks_putback(philo_g_ptr);
		if (philo_g_ptr->args_main[NOM_EAT] > 0)
		{
			philo_g_ptr->philosopher->nom_to_eat--;
			if (philo_g_ptr->philosopher->nom_to_eat == 0)
				sem_post(philo_g_ptr->sem_has_to_eat);
		}
	}
}

void	ph_act_is_dead(t_philo_global *philo_g_ptr)
{
	t_philosopher	*philosopher;
	ssize_t			t_stamp;
	int				i;

	philosopher = philo_g_ptr->philosopher;
	t_stamp = ph_get_time();
	if ((t_stamp - ph_safe_value_get(&philosopher->s_last_ate)) >= \
	philo_g_ptr->args_main[TT_DIE] * 1000)
	{
		ph_print_event(philo_g_ptr, STATUS_DIE);
		sem_post(philo_g_ptr->sem_exit);
		if (philo_g_ptr->args_main[NOM_EAT] > 0)
		{
			i = 0;
			while (i++ < philo_g_ptr->args_main[NOM_PHILO])
				sem_post(philo_g_ptr->sem_has_to_eat);
		}
	}
}

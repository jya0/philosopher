/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:18:47 by jyao              #+#    #+#             */
/*   Updated: 2022/10/08 03:10:39 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int value of 1 means it failed to lock the fork
**0 means it succeeded in locking the fork.
*/
int	ph_act_forks_trytake(t_philosopher *philosopher)
{
	int	ret_val;

	if (philosopher->l_fork == philosopher->r_fork)
		return (1);
	ret_val = 1;
	pthread_mutex_lock(&philosopher->l_fork->mutex);
	pthread_mutex_lock(&philosopher->r_fork->mutex);
	if (philosopher->l_fork->value == FORK_UNLOCKED \
	&& philosopher->r_fork->value == FORK_UNLOCKED \
	&& philosopher->l_fork->history != philosopher->id \
	&& philosopher->r_fork->history != philosopher->id)
	{
		philosopher->l_fork->value = FORK_LOCKED;
		philosopher->r_fork->value = FORK_LOCKED;
		philosopher->l_fork->history = philosopher->id;
		philosopher->r_fork->history = philosopher->id;
		ret_val = 0;
	}
	pthread_mutex_unlock(&philosopher->r_fork->mutex);
	pthread_mutex_unlock(&philosopher->l_fork->mutex);
	return (ret_val);
}

void	ph_act_forks_putback(t_philosopher *philosopher)
{
	ph_safe_value_set(philosopher->r_fork, FORK_UNLOCKED);
	ph_safe_value_set(philosopher->l_fork, FORK_UNLOCKED);
}

int	ph_act_think(t_philosopher *philosopher)
{
	ph_print_event(philosopher, STATUS_THINK);
	while (ph_check_all_philos(philosopher) == 0)
	{
		if (ph_act_forks_trytake(philosopher) == 0)
		{
			ph_print_event(philosopher, STATUS_TAKE_FORK);
			return (0);
		}
		usleep(USLEEP_INTERVAL);
	}
	return (1);
}

/*this is for sleep and eat*/
int	ph_act_eat_sleep(\
t_philosopher	*philosopher, int e_status, size_t time_usec)
{
	size_t	target;

	ph_print_event(philosopher, e_status);
	if (e_status == STATUS_EAT)
		philosopher->t_last_eat = ph_get_time();
	philosopher->t_stamp = ph_get_time();
	target = philosopher->t_stamp + time_usec;
	while (philosopher->t_stamp < target)
	{
		if (ph_check_all_philos(philosopher))
			return (1);
		usleep(USLEEP_INTERVAL);
		philosopher->t_stamp = ph_get_time();
	}
	if (e_status == STATUS_EAT)
	{
		ph_act_forks_putback(philosopher);
		if (philosopher->philo_g_ptr->args_main[NOM_EAT] > 0)
		{
			philosopher->nom_eat--;
			if (philosopher->nom_eat == 0)
				ph_safe_value_change(&philosopher->philo_g_ptr->s_ate, -1);
		}
	}
	return (0);
}

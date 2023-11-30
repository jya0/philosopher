/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:03:52 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 17:55:21 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_thread_routine(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	philosopher->t_last_eat = ph_get_time();
	while (ph_check_all_philos(philosopher) == 0)
	{
		if (ph_act_think(philosopher))
			break ;
		if (ph_act_eat_sleep(philosopher, STATUS_EAT, \
			philosopher->philo_g_ptr->args_main[TT_EAT] * 1000))
			break ;
		if (ph_act_eat_sleep(philosopher, STATUS_SLEEP, \
			philosopher->philo_g_ptr->args_main[TT_SLEEP] * 1000))
			break ;
	}
	return (NULL);
}

static int	ph_is_philo_dead(t_philosopher *philosopher)
{
	philosopher->t_stamp = ph_get_time();
	if (philosopher->t_stamp - philosopher->t_last_eat \
	>= (size_t)philosopher->philo_g_ptr->args_main[TT_DIE] * 1000)
	{
		ph_print_event(philosopher, STATUS_DIE);
		return (1);
	}
	return (0);
}

static int	ph_are_philos_finished_eating(t_philo_global *philo_g_ptr)
{
	return (philo_g_ptr->args_main[NOM_EAT] >= 0 \
	&& ph_safe_value_get(&philo_g_ptr->s_ate) <= 0);
}

int	ph_check_all_philos(t_philosopher *philosopher)
{
	return (ph_are_philos_finished_eating(philosopher->philo_g_ptr) \
	|| ph_is_philo_dead(philosopher));
}

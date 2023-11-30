/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_event.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:55:32 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 17:57:32 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ph_choose_message(int e_state)
{
	if (e_state == STATUS_THINK)
		return (COLOR_YELLOW"is thinking");
	else if (e_state == STATUS_TAKE_FORK)
		return (COLOR_WHITE"has taken a fork");
	else if (e_state == STATUS_EAT)
		return (COLOR_GREEN"is eating");
	else if (e_state == STATUS_SLEEP)
		return (COLOR_BLUE"is sleeping");
	else if (e_state == STATUS_DIE)
		return (COLOR_RED"died");
	return (NULL);
}

/*gives answer in microseconds*/
size_t	ph_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 * 1000 + time.tv_usec);
}

void	ph_print_event(t_philosopher *philosopher, int e_status)
{
	pthread_mutex_lock(&philosopher->philo_g_ptr->s_event.mutex);
	if (ph_safe_value_get(&philosopher->philo_g_ptr->s_exit) != EXIT_NONE)
	{
		pthread_mutex_unlock(&philosopher->philo_g_ptr->s_event.mutex);
		return ;
	}
	if (e_status == STATUS_DIE)
		ph_safe_value_set(&philosopher->philo_g_ptr->s_exit, EXIT_START);
	philosopher->t_stamp = ph_get_time();
	printf("{%ld} %d %s\n"COLOR_RESET, \
	(philosopher->t_stamp - philosopher->philo_g_ptr->t_stamp_offset) / 1000, \
	philosopher->id + 1, ph_choose_message(e_status));
	if (e_status == STATUS_TAKE_FORK)
		printf("{%ld} %d %s\n"COLOR_RESET, \
		(philosopher->t_stamp - \
		philosopher->philo_g_ptr->t_stamp_offset) / 1000, \
		philosopher->id + 1, ph_choose_message(e_status));
	pthread_mutex_unlock(&philosopher->philo_g_ptr->s_event.mutex);
}

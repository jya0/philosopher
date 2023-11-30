/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_event_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:55:32 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 22:27:26 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
ssize_t	ph_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 * 1000 + time.tv_usec);
}

void	ph_print_event(t_philo_global	*philo_g_ptr, int e_status)
{
	ssize_t			t_stamp;

	sem_wait(philo_g_ptr->sem_print);
	t_stamp = ph_get_time();
	printf("{%ld} %d %s\n"COLOR_RESET, \
	(t_stamp - philo_g_ptr->t_stamp_offset) / 1000, \
	philo_g_ptr->philosopher->id, ph_choose_message(e_status));
	if (e_status == STATUS_TAKE_FORK)
		printf("{%ld} %d %s\n"COLOR_RESET, \
		(t_stamp - philo_g_ptr->t_stamp_offset) / 1000, \
		philo_g_ptr->philosopher->id, ph_choose_message(e_status));
	if (e_status == STATUS_DIE)
		return ;
	sem_post(philo_g_ptr->sem_print);
}

/*
static int	get_philo_id(pid_t	*all_pid, pid_t	pid, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (pid == all_pid[i])
			return (i + 1);
		i++;
	}
	return (-1);
}
*/

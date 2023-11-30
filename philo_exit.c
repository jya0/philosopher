/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:33:50 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 18:20:23 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_destroy_mutexes(t_philo_global *philo_g_ptr)
{
	int	i;

	if (!philo_g_ptr->forks)
		return ;
	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		pthread_mutex_destroy(&philo_g_ptr->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&philo_g_ptr->s_ate.mutex);
	pthread_mutex_destroy(&philo_g_ptr->s_exit.mutex);
	pthread_mutex_destroy(&philo_g_ptr->s_event.mutex);
	free(philo_g_ptr->forks);
}

static void	ph_free_philosophers(t_philo_global *philo_g_ptr)
{
	if (!philo_g_ptr->philosophers)
		return ;
	free(philo_g_ptr->philosophers);
}

int	ph_exit(t_philo_global	*philo_g_ptr)
{
	if (!philo_g_ptr)
		exit(1);
	ph_destroy_mutexes(philo_g_ptr);
	ph_free_philosophers(philo_g_ptr);
	if (philo_g_ptr->args_main)
		free(philo_g_ptr->args_main);
	exit(0);
	return (0);
}

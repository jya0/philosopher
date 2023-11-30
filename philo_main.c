/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:41:20 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 17:48:26 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_threads_create(t_philo_global *philo_g_ptr)
{
	int	i;

	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		if (pthread_create(\
		&philo_g_ptr->philosophers[i].thread, NULL, \
		ph_thread_routine, (void *)&philo_g_ptr->philosophers[i]))
			ph_exit(philo_g_ptr);
		i++;
	}
}

static void	ph_threads_join(t_philo_global *philo_g_ptr)
{
	int	i;

	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		if (pthread_join(philo_g_ptr->philosophers[i].thread, NULL))
			ph_exit(philo_g_ptr);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo_global	philo_global;

	if (argc - ARGS_COUNT > 1 || argc - ARGS_COUNT < 0)
		return (1);
	ph_init_global(argc, argv, &philo_global);
	ph_threads_create(&philo_global);
	ph_threads_join(&philo_global);
	ph_exit(&philo_global);
	return (0);
}

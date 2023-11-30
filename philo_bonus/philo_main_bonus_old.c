/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:41:20 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 18:38:18 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_processes(t_philo_global *philo_g_ptr)
{
	int				i;

	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		philo_g_ptr->all_pid[i] = fork();
		if (philo_g_ptr->all_pid[i] < 0)
			ph_exit(philo_g_ptr);
		else if (philo_g_ptr->all_pid[i] != 0)
			i++;
		else if (philo_g_ptr->all_pid[i] == 0)
		{
			ph_init_philosopher(philo_g_ptr, i + 1);
			ph_philo_process(philo_g_ptr);
		}
	}
}

static void	check_all_have_eaten(t_philo_global *philo_g_ptr)
{
	int	i;

	if (philo_g_ptr->args_main[NOM_EAT] <= 0)
		return ;
	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		sem_wait(philo_g_ptr->sem_has_to_eat);
		i++;
	}
	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		sem_post(philo_g_ptr->sem_exit);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo_global	philo_global;

	if (argc - ARGS_COUNT > 1 || argc - ARGS_COUNT < 0)
		return (1);
	ph_init_global(argc, argv, &philo_global);
	create_processes(&philo_global);
	check_all_have_eaten(&philo_global);
	ph_exit(&philo_global);
	return (0);
}

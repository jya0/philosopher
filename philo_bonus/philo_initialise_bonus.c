/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialise_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:37:01 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 22:47:58 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_args_main(int argc, char *argv[], \
t_philo_global *philo_g_ptr)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		philo_g_ptr->args_main[i] = ph_atoi(argv[i + 1], philo_g_ptr);
		i++;
	}
	if (philo_g_ptr->args_main[NOM_PHILO] == 0)
		ph_exit(philo_g_ptr);
	if (argc == ARGS_COUNT)
		philo_g_ptr->args_main[NOM_EAT] = -1;
}

int	ph_init_global(int argc, char *argv[], \
t_philo_global *philo_g_ptr)
{
	*philo_g_ptr = (t_philo_global){0};
	init_args_main(argc, argv, philo_g_ptr);
	ph_init_semaphore(philo_g_ptr, &philo_g_ptr->sem_exit, SEM_EXIT, 0);
	ph_init_semaphore(philo_g_ptr, &philo_g_ptr->sem_print, SEM_PRINT, 1);
	ph_init_semaphore(philo_g_ptr, &philo_g_ptr->sem_forks, SEM_FORKS, \
		philo_g_ptr->args_main[NOM_PHILO]);
	ph_init_semaphore(philo_g_ptr, &philo_g_ptr->sem_has_to_eat, \
		SEM_HAS_TO_EAT, 0);
	philo_g_ptr->all_pid = (pid_t *)ph_calloc(\
	philo_g_ptr->args_main[NOM_PHILO], sizeof(pid_t));
	if (!philo_g_ptr->all_pid)
		ph_exit(philo_g_ptr);
	philo_g_ptr->t_stamp_offset = ph_get_time();
	return (0);
}

static char	*create_sem_name(const char *name_stem, int id)
{
	char	*num_str;
	char	*bin_sem_name;

	num_str = philo_itoa(id);
	bin_sem_name = philo_strjoin(name_stem, num_str);
	free(num_str);
	return (bin_sem_name);
}

void	ph_init_semaphore(t_philo_global *philo_g_ptr, sem_t **sem_ptr, \
const char	*sem_name, int value)
{
	sem_unlink(sem_name);
	*sem_ptr = sem_open(sem_name, O_CREAT | O_EXCL, S_IRGRP | S_IWGRP, value);
	if (*sem_ptr == SEM_FAILED)
		ph_exit(philo_g_ptr);
}

void	ph_init_philosopher(t_philo_global *philo_g_ptr, int id)
{
	philo_g_ptr->philosopher = \
	(t_philosopher *)ph_calloc(1, sizeof(t_philosopher));
	if (!philo_g_ptr->philosopher)
		ph_exit(philo_g_ptr);
	philo_g_ptr->philosopher->id = id;
	philo_g_ptr->philosopher->nom_to_eat = philo_g_ptr->args_main[NOM_EAT];
	philo_g_ptr->philosopher->s_last_ate.sem_name = \
	create_sem_name("sem_last_ate_", id);
	ph_init_semaphore(philo_g_ptr, \
	&philo_g_ptr->philosopher->s_last_ate.bin_sem, \
	philo_g_ptr->philosopher->s_last_ate.sem_name, 1);
}

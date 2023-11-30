/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:37:01 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 18:17:26 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args_main(int argc, char *argv[], \
t_philo_global *philo_g_ptr)
{
	int	i;

	philo_g_ptr->args_main = (int *)ph_calloc(ARGS_COUNT, sizeof(int));
	if (!philo_g_ptr->args_main)
		ph_exit(philo_g_ptr);
	i = 0;
	while (i < argc - 1)
	{
		philo_g_ptr->args_main[i] = ph_atoi(argv[i + 1], philo_g_ptr);
		i++;
	}
	if (argc - 1 == ARGS_COUNT - 1)
		philo_g_ptr->args_main[NOM_EAT] = -1;
}

static void	init_safes(t_philo_global *philo_g_ptr)
{
	if (pthread_mutex_init(&philo_g_ptr->s_event.mutex, NULL) || \
	pthread_mutex_init(&philo_g_ptr->s_exit.mutex, NULL) || \
	pthread_mutex_init(&philo_g_ptr->s_ate.mutex, NULL))
		ph_exit(philo_g_ptr);
	if (philo_g_ptr->args_main[NOM_EAT] > 0)
		philo_g_ptr->s_ate.value = philo_g_ptr->args_main[NOM_PHILO];
}

/*think of a clockwise clock starting from 12*/
static void	init_philosophers(t_philo_global *philo_g_ptr)
{
	int	i;

	philo_g_ptr->philosophers = \
	(t_philosopher *)ph_calloc(philo_g_ptr->args_main[NOM_PHILO], \
		sizeof(t_philosopher));
	if (!philo_g_ptr->philosophers)
		ph_exit(philo_g_ptr);
	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		philo_g_ptr->philosophers[i] = (t_philosopher) \
		{.id = i, .l_fork = &philo_g_ptr->forks[i], \
		.r_fork = &philo_g_ptr->forks[i + 1], \
		.nom_eat = philo_g_ptr->args_main[NOM_EAT], \
		.philo_g_ptr = philo_g_ptr};
		i++;
	}
	philo_g_ptr->philosophers[i - 1].l_fork = &philo_g_ptr->forks[0];
	philo_g_ptr->philosophers[i - 1].r_fork = &philo_g_ptr->forks[i - 1];
}

static void	init_forks(t_philo_global *philo_g_ptr)
{
	int	i;

	philo_g_ptr->forks = (t_safe *)ph_calloc(\
	philo_g_ptr->args_main[NOM_PHILO], sizeof(t_safe));
	if (!philo_g_ptr->forks)
		ph_exit(philo_g_ptr);
	i = 0;
	while (i < philo_g_ptr->args_main[NOM_PHILO])
	{
		if (pthread_mutex_init(&philo_g_ptr->forks[i].mutex, NULL))
			ph_exit(philo_g_ptr);
		philo_g_ptr->forks[i].value = FORK_UNLOCKED;
		philo_g_ptr->forks[i].history = FORK_UNLOCKED;
		i++;
	}
}

int	ph_init_global(int argc, char *argv[], \
t_philo_global *philo_g_ptr)
{
	*philo_g_ptr = (t_philo_global){0};
	init_args_main(argc, argv, philo_g_ptr);
	if (philo_g_ptr->args_main[NOM_PHILO] == 0)
		ph_exit(philo_g_ptr);
	init_forks(philo_g_ptr);
	init_safes(philo_g_ptr);
	init_philosophers(philo_g_ptr);
	philo_g_ptr->t_stamp_offset = ph_get_time();
	return (0);
}

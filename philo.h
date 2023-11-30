/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:22:39 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 17:47:49 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*COLORS FOR PRINTF*/
# define COLOR_RESET	"\033[0m"
# define COLOR_BLUE 	"\033[0;34m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_RED		"\033[0;31m"
# define COLOR_WHITE	"\033[0;37m"
# define COLOR_YELLOW	"\033[0;33m"

# define USLEEP_INTERVAL 42

/*
** no_must_eat is an optional arg
** tt_eat, _die, _sleep should all be in milliseconds
*/

enum	e_event {
	STATUS_CREATED,
	STATUS_THINK,
	STATUS_TAKE_FORK,
	STATUS_EAT,
	STATUS_SLEEP,
	STATUS_DIE,
	STATUS_FINISHED
};

enum	e_fork_value {
	FORK_UNLOCKED = -1,
	FORK_LOCKED = -2
};

enum	e_exit {
	EXIT_NONE,
	EXIT_START,
	EXIT_COMPLETE
};

typedef struct s_safe {
	pthread_mutex_t	mutex;
	int				value;
	int				history;
}	t_safe;

typedef struct s_philosopher {
	pthread_t						thread;
	int								id;
	t_safe							*l_fork;
	t_safe							*r_fork;
	int								nom_eat;
	size_t							t_last_eat;
	size_t							t_stamp;
	struct s_philo_global			*philo_g_ptr;
}	t_philosopher;

/*NOM_EAT is an optional argument*/
enum	e_args_main {
	NOM_PHILO,
	TT_DIE,
	TT_EAT,
	TT_SLEEP,
	NOM_EAT,
	ARGS_COUNT
};

typedef struct s_philo_global {
	int				*args_main;
	t_philosopher	*philosophers;
	size_t			t_stamp_offset;
	t_safe			*forks;
	t_safe			s_event;
	t_safe			s_exit;
	t_safe			s_ate;
}	t_philo_global;

/*philo_initialise.c*/
int		ph_init_global(int argc, char *argv[], \
t_philo_global *philo_g_ptr);

/*philo_atoi.c*/
int		ph_atoi(const char *str, t_philo_global *philo_g_ptr);

/*philo_calloc.c*/
void	*ph_calloc(size_t nitems, size_t size);

/*philo_print_event.c*/
void	ph_print_event(t_philosopher *philosopher, int e_status);
size_t	ph_get_time(void);
void	ph_announce_death(t_philo_global *philo_g_ptr);

/*philo_action.c*/
int		ph_act_forks_trytake(t_philosopher *philosopher);
void	ph_act_forks_putback(t_philosopher *philosopher);
int		ph_act_eat_sleep(\
t_philosopher	*philosopher, int e_status, size_t time_usec);
int		ph_act_think(t_philosopher *philosopher);

/*philo_safe.c*/
int		ph_safe_value_get(t_safe *safe_ptr);
void	ph_safe_value_set(t_safe *safe_ptr, int value);
void	ph_safe_value_change(t_safe *safe_ptr, int change);

/*philo_exit.c*/
int		ph_exit(t_philo_global	*philo_g_ptr);

/*philo_thread_routine.c*/
void	*ph_thread_routine(void *args);
int		ph_check_all_philos(t_philosopher *philosopher);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:22:39 by jyao              #+#    #+#             */
/*   Updated: 2022/10/22 22:38:45 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/*COLORS FOR PRINTF*/
# define COLOR_RESET	"\033[0m"
# define COLOR_BLUE 	"\033[0;34m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_RED		"\033[0;31m"
# define COLOR_WHITE	"\033[0;37m"
# define COLOR_YELLOW	"\033[0;33m"

# define USLEEP_INTERVAL 42

/*SHARED SEM NAMES*/
# define SEM_EXIT		"sem_exit"
# define SEM_PRINT		"sem_print"
# define SEM_HAS_TO_EAT	"sem_has_to_eat"
# define SEM_FORKS		"sem_forks"

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

enum	e_exit {
	EXIT_NONE,
	EXIT_START,
	EXIT_DEAD
};

typedef struct s_safe {
	sem_t			*bin_sem;
	char			*sem_name;
	ssize_t			value;
}	t_safe;

/*NOM_EAT is an optional argument*/
enum	e_args_main_index {
	NOM_PHILO,
	TT_DIE,
	TT_EAT,
	TT_SLEEP,
	NOM_EAT,
	ARGS_COUNT
};

typedef struct s_philosopher {
	pthread_t						th_is_alive;
	int								id;
	int								nom_to_eat;
	int								is_fork;
	t_safe							s_is_exit;
	t_safe							s_last_ate;
}	t_philosopher;

typedef struct s_philo_global {
	int				args_main[ARGS_COUNT];
	t_philosopher	*philosopher;
	sem_t			*sem_exit;
	sem_t			*sem_print;
	sem_t			*sem_has_to_eat;
	sem_t			*sem_forks;
	pid_t			*all_pid;
	ssize_t			t_stamp_offset;
}	t_philo_global;

/*philo_initialise.c*/
int				ph_init_global(int argc, char *argv[], \
t_philo_global *philo_g_ptr);
void			ph_init_semaphore(t_philo_global *philo_g_ptr, sem_t **sem_ptr, \
const char	*sem_name, int value);

/*philo_atoi.c*/
int				ph_atoi(const char *str, t_philo_global *philo_g_ptr);

/*philo_calloc.c*/
void			*ph_calloc(size_t nitems, size_t size);

/*philo_strjoin.c*/
char			*philo_strjoin(const char *s1, const char *s2);

/*philo_itoa.c*/
char			*philo_itoa(int n);

/*philo_usleep_bonus.c*/
void			ph_usleep(ssize_t	usec_period);

/*philo_print_event.c*/
void			ph_print_event(t_philo_global *philo_g_ptr, int e_status);
ssize_t			ph_get_time(void);

/*philo_action.c*/
void			ph_act_eat_sleep(\
t_philo_global *philo_g_ptr, int e_status, ssize_t time_usec);
void			ph_act_think(t_philo_global *philo_g_ptr);
void			ph_act_forks_putback(t_philo_global *philo_g_ptr);
void			ph_act_forks_take(t_philo_global *philo_g_ptr);
void			ph_act_is_dead(t_philo_global *philo_g_ptr);

/*philo_safe.c*/
ssize_t			ph_safe_value_get(t_safe *safe_ptr);
void			ph_safe_value_set(t_safe *safe_ptr, ssize_t value);
void			ph_safe_value_change(t_safe *safe_ptr, ssize_t change);

/*philo_exit.c*/
void			ph_exit(t_philo_global	*philo_g_ptr);
void			ph_everyone_exit(t_philo_global	*philo_g_ptr);

/*philo_thread_routine.c*/
void			ph_init_philosopher(t_philo_global *philo_g_ptr, int id);
void			ph_philo_process(t_philo_global	*philo_g_ptr);

#endif
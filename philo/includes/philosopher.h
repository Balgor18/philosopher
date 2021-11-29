/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/29 19:07:13 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pthread_create() --> cree un thread qui se lance en simultane avec le code
// Il lance la fonction routine
// avec l'arg en premier argument

// Le thread s'arrete soit avec des return
// Soit avec pthread_exit(can't be used)
// ----------------------------------------------------------------------------
// pthread_detach() --> prends le thread pour le detache
// Fais en sorte que toutes memoire use par ce thread sera rendue a la fin
// Helas les thread se desyncronise avec pthread_join()
// ----------------------------------------------------------------------------
// pthread_join() --> suspend l'exectution du thread
// tant que th nas pas fini sont execution
// ----------------------------------------------------------------------------
// pthread_mutex_init() --> initialise mutex selon les attributs
// spécifié par mutexattr.
// Si mutexattr vaut NULL, les paramètres par défaut sont utilisés.
// ----------------------------------------------------------------------------
// pthread_mutex_destroy() --> détruit un mutex.
// libérant les ressources qu'il détient.
// Le mutex doit être déverrouillé.
// ----------------------------------------------------------------------------
// pthread_mutex_lock() --> verrouille le mutex.
// Si le mutex est déverrouillé, il devient verrouillé
// possédé par le thread appelant et pthread_mutex_lock()
// rend la main immédiatement.
// Si le mutex est déjà verrouillé par un autre thread.
// pthread_mutex_lock suspend le thread appelant
// jusqu'à ce que le mutex soit déverrouillé.
// ----------------------------------------------------------------------------
// pthread_mutex_unlock() --> déverrouille le mutex.

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include "color.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define FAILURE 0

extern int nb_print;

typedef enum e_param
{
	NB_PHILO = 0,
	TIME_TO_DIE,
	TIME_TO_SLEEP,
	TIME_TO_EAT,
	MAX_EAT_COUNT,
	PARAM_MAX,
}				t_param;

typedef pthread_mutex_t			t_fork;

typedef unsigned long long int	t_time;

typedef struct s_check			t_check;

typedef struct s_philo
{
	int					nb;// need
	int					nb_eat;
	int					fork_left;
	int					fork_right;
	pthread_t			thread;// thread du philo
	// pthread_mutex_t		*mutex_alive;// if dead
	// pthread_mutex_t		*all_eat;// just create
	// int					*alive;// value for dead
	t_time				last_eat;// last time_t philo eat
	pthread_mutex_t		lock_eat;
	// t_fork				*fork_left;//fork
	// t_fork				*fork_right;// fork
	t_check				*check;

	// t_fork				*forks;
}				t_philo;

struct s_check
{
	long			*param;
	int				g_nb_meal;
	int				everyone_alive;
	t_philo			*philos;
	pthread_mutex_t	update_nb_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	prompt;
	pthread_mutex_t	check_end;
};

// https://github.com/Sheschire/Philosophers.git
// https://github.com/Alexdelia/42-Philosophers.git
// https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=3

/*
**----------------------------------
**--------------Parse---------------
**----------------------------------
*/
int			verif_parse(int argc, char **argv, int *param);

/*
**----------------------------------
**--------------Philo---------------
**----------------------------------
*/
int			start_philo(t_param *param, pthread_t *philo);
int			create_philo(t_param *param, pthread_t *philo);
t_philo		*philo_init(int *param, t_philo *philo);
void		change_state(t_philo *philo, t_status new_state);

/*
**----------------------------------
**---------------Time---------------
**----------------------------------
*/
t_time		get_time(void);
void		ft_sleep(unsigned long long dur_ms);

/*
**----------------------------------
**-------------Routine--------------
**----------------------------------
*/
int			start_routine(t_param *param);
void		*routine(t_philo *philo);

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/

// Fct print Error\n and the message
// Return False = 0
int			error_msg(char *s);
int			error_arg(int argc);
/*
**----------------------------------
**--------------Print---------------
**----------------------------------
*/
void	ft_print(char *s, int nb, t_time time, int print);

/*
**----------------------------------
**------------Includes--------------
**----------------------------------
*/
int			ft_atoi(char *c);
void		ft_putstr_fd(int fd, char *s);
size_t		ft_strlen(char *s);

#endif

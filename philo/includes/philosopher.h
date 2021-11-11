/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 16:15:54 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pthread_create() --> cree un thread qui se lance en simultane avec le code
// Il lance la fonction routine
// avec l'arg en premier argument

// Le thread s'arrete soit avec des return
// Soit avec  pthread_exit
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
# include "color.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define FAILURE 0

typedef struct s_param
{
	int	nb_philo;
	int	nb_fork;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_think;
	int	many_time_eat;
}				t_param;

/*
**----------------------------------
**--------------Parse---------------
**----------------------------------
*/
int			parse(int argc, char **argv, t_param *param);

/*
**----------------------------------
**--------------Philo---------------
**----------------------------------
*/
int			start_philo();

/*
**----------------------------------
**---------------Time---------------
**----------------------------------
*/
uint64_t	get_time();

/*
**----------------------------------
**-------------Routine--------------
**----------------------------------
*/
int			start_routine(t_param *param);
int			routine();

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/

// Fct print Error\n and the message
// Return False = 0
int			error_msg(char *s);

// Fct print how to use the binary file
// return EXIT_FAILURE
int			error_arg(void);

/*
**----------------------------------
**------------Includes--------------
**----------------------------------
*/
int			ft_atoi(char *c);
void		ft_putstr_fd(int fd, char *s);

#endif

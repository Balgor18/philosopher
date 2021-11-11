/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 09:25:00 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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
	int	many_time_eat;
}				t_param;

typedef struct s_philo
{
	int	fork_left;
	int	fork_right;
}				t_philo;

/*
**----------------------------------
**--------------Parse---------------
**----------------------------------
*/
int		parse(int argc, char **argv, t_param *param);

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/

// Fct print Error\n and the message
// Return False = 0
int		error_msg(char *s);

// Fct print how to use the binary file
// return EXIT_FAILURE
int		error_arg(void);

/*
**----------------------------------
**--------------Philo---------------
**----------------------------------
*/
int		start_philo();

/*
**----------------------------------
**------------Includes--------------
**----------------------------------
*/
int		ft_atoi(char *c);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(int fd, char *s);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/08 20:15:07 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <string.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define FAILURE 0

typedef struct s_param
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	many_time_eat;
}				t_param;

/*
**----------------------------------
**-------------Parse----------------
**----------------------------------
*/
int		parse(int argc, char **argv, t_param *param);

/*
**----------------------------------
**------------Includes--------------
**----------------------------------
*/
int		ft_atoi(char *c);
void	ft_bzero(void *s, size_t n);

#endif

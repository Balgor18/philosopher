/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:10:59 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/09 15:15:56 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static size_t	ft_strlen(char *s)
{
	char *tmp;

	tmp = s;
	while (*s)
		s++;
	return (s - tmp);
}

void	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

// Fct print Error\n and the message
// Return False = 0
int	error_msg(char *s)
{
	ft_putstr_fd(STDERR, RED"Error\n"WHITE);
	ft_putstr_fd(STDERR, s);
	return (FALSE);
}

// Fct print how to use the binary file
// return EXIT_FAILURE
int	error_arg(void)
{
	ft_putstr_fd(STDERR, RED"Error\n"WHITE);
	ft_putstr_fd(STDERR, "usage :"CYAN" ./philo "GREEN"nb_philo time_die time_eat");
	ft_putstr_fd(STDERR, " time_sleep "WHITE"[nb_philo_eat]\n");
	return (EXIT_FAILURE);
}

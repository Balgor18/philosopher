/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:10:59 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/18 14:25:24 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
int	error_arg(int argc)
{
	if (argc == 1)
	{
		ft_putstr_fd(STDERR, RED"Error\n"WHITE);
		ft_putstr_fd(STDERR, "usage :"CYAN" ./philo ");
		ft_putstr_fd(STDERR, GREEN"nb_philo time_die time_eat");
		ft_putstr_fd(STDERR, " time_sleep "WHITE"[nb_philo_eat]\n");
	}
	else if (argc <= 4)
		error_msg("Not enought arg\n");
	else if (argc >= 7)
		error_msg("Too enought arg\n");
	return (EXIT_FAILURE);
}

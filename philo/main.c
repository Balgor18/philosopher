/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:40:19 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/13 10:57:27 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Fct print how to use the binary file
// return EXIT_FAILURE
static int	error_arg(int argc)
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

int	main(int argc, char **argv)
{
	t_param		param;
	pthread_t	*philo;

	param = (t_param){0};
	if (argc == 5 || argc == 6)
	{
		if (!verif_parse(argc, argv, &param))
			return (EXIT_FAILURE);
		philo = malloc(sizeof(pthread_t) * param.nb_philo);
		if (!philo)
			return (EXIT_FAILURE);
		if (!philo(&param, philo))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (error_arg(argc));
}

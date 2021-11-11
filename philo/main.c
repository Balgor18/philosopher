/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:40:19 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/09 16:13:21 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*philo;

	param = (t_param){};
	if (argc == 1)
		return (error_arg());
	if (argc == 5 || argc == 6)
	{
		if (!parse(argc, argv, &param))
			return (EXIT_FAILURE);
		philo = malloc(sizeof(t_philo) * param.nb_philo);
		if (!philo)
			return (EXIT_FAILURE);
		if (!start_philo())
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	error_msg("Not enought arg\n");
	return (EXIT_FAILURE);
}
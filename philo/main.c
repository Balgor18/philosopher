/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:45:08 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 17:18:38 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_check			check;
	int	i;

	check = (t_check) {0};
	if (!verif_arg(ac, av))
	{
		error_msg("Arguments not valids\n");
		return (1);
	}
	init_check(&check, av);
	init_philo(&check);
	start(&check);
	i = -1;
	while (++i < check.nb_philo)
	{
		if (pthread_join(check.philos[i].thread, NULL))
			error_msg("failed_joined");
		if (pthread_join(check.philos[i].watcher, NULL))
			error_msg("failed_joined");
	}
	end_simulation(&check);
	return (0);
}

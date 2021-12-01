/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:45:08 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 23:56:48 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init(t_check *check, char **argv)
{
	if (!init_struct_check(check, argv))
		return (0);
	if (!init_struct_philo(check))
	{
		free(check->forks);
		free(check->philos);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_check			check;
	int				i;

	check = (t_check){0};
	if (!parse_verif_arg(argc, argv))
	{
		error_msg("Arguments not valids\n");
		return (1);
	}
	if (!init(&check, argv))
		return (1);
	start(&check);
	i = -1;
	while (++i < check.nb_philo)
	{
		if (pthread_join(check.philos[i].thread, NULL))
			error_msg("failed_joined");
		if (pthread_join(check.philos[i].watcher, NULL))
			error_msg("failed_joined");
	}
	stop(&check);
	return (0);
}

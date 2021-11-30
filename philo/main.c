/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:45:08 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/30 16:59:55 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_check *check, long *param)
{
	int	nb;

	nb = -1;
	check->param = param;
	while (++nb < param[NB_PHILO])
	{
		check->philos[nb].nb = nb;
		check->philos[nb].nb_eat = 0;
		check->philos[nb].fork_left = (nb + 1) % check->param[NB_PHILO];
		check->philos[nb].fork_right = nb;
		check->philos[nb].check = check;
		if (pthread_mutex_init(&check->forks[nb], NULL))
		{
			error_msg("mutex_init");
			return ;
		}
		if (pthread_mutex_init(&check->philos[nb].lock_eat, NULL))
		{
			error_msg("mutex_init");
			return ;
		}
	}
	if (pthread_mutex_init(&check->is_print, NULL))
		error_msg("mutex_init");
	if (pthread_mutex_init(&check->check_nb_meal, NULL))
		error_msg("mutex_init");
	if (pthread_mutex_init(&check->check_finish, NULL))
		error_msg("mutex_init");
}

int	main(int ac, char **av)
{
	t_check			check;
	static long		param[PARAM_MAX];
	int	i;

	check = (t_check) {0};
	if (!verif_arg(ac, av))
		error_msg("Arguments not valids\n");
	init_check(&check, param, av);
	init_philo(&check, param);
	start(&check);
	i = -1;
	while (++i < check.param[NB_PHILO])
	{
		if (pthread_join(check.philos[i].thread, NULL))
			error_msg("failed_joined");
		if (pthread_join(check.philos[i].watcher, NULL))
			error_msg("failed_joined");
	}
	end_simulation(&check);
	return (0);
}

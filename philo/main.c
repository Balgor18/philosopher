/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:45:08 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/29 18:17:28 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_check *check, long *param)
{
	int	nb;

	nb = -1;
	while (++nb < param[NB_PHILO])
	{
		check->philos[nb].nb = nb;
		check->philos[nb].nb_eat = 0;
		check->philos[nb].fork_left = (nb + 1) % check->param[NB_PHILO];
		check->philos[nb].fork_right = nb;
		check->philos[nb].check = check;
		if (pthread_mutex_init(&check->forks[nb], NULL))
		{
			err_msg("Mutex init failed. (forks)");
			return ;
		}
		// if (pthread_mutex_init(&check->philos[nb].lock_meal, NULL))
		// {
		// 	err_msg("Mutex init failed. (lock_meal)");
		// 	return ;
		// }
	}
	if (pthread_mutex_init(&check->prompt, NULL))
		err_msg("Mutex init failed. (prompt)");
	if (pthread_mutex_init(&check->update_nb_meal, NULL))
		err_msg("Mutex init failed. (update_nb_meal)");
	if (pthread_mutex_init(&check->check_end, NULL))
		err_msg("Mutex init failed. (check_end)");
}

int	main(int ac, char **av)
{
	t_check	check;
	static long		param[PARAM_MAX];

	if (!check_arg(ac, av))// check
		err_msg("Arguments not valids\n");
	init_check(&check, param, av);
	init_philo(&check, param);
	// start_simulation(&d);
	// while (++id < d.nb_philo)
	// {
	// 	if (pthread_join(d.philos[id].thread_id, NULL))
	// 		_err("Failed in joining thread. (Philos)");
	// 	if (pthread_join(d.philos[id].monitor, NULL))
	// 		_err("Failed in joining thread. (Monitor)");
	// }
	// end_simulation(&d);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:26:47 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 17:47:45 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_check(t_check *c, char **argv)
{
	c->nb_philo = ft_atoi(argv[1]);
	if (c->nb_philo > 200 || c->nb_philo == 0)
	{
		error_msg("numb Philosophers\n");
		return ;
	}
	c->die_time = ft_atoi(argv[2]);
	if (c->die_time == 0)
	{
		error_msg("Time of death\n");
		return ;
	}
	c->eat_time = ft_atoi(argv[3]);
	c->sleep_time = ft_atoi(argv[4]);
	c->need_nb_eat = -1;
	c->nb_philo_done_eat = 0;
	c->everyone_alive = 1;
	if (argv[5])
		c->need_nb_eat = ft_atoi(argv[5]);
	c->tstart = get_time();
	c->philos = (t_philo *)malloc(sizeof(t_philo) * c->nb_philo);
	if (!c->philos)
	{
		error_msg("Malloc");
		return ;
	}
	c->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * c->nb_philo);
	if (!c->forks)
	{
		if (c->philos)
			free(c->philos);
		error_msg("Malloc");
		return ;
	}
}

void	init_philo(t_check *check)
{
	int	nb;

	nb = -1;
	while (++nb < check->nb_philo)
	{
		check->philos[nb].nb = nb;
		check->philos[nb].nb_eat = 0;
		check->philos[nb].fork_left = (nb + 1) % check->nb_philo;
		check->philos[nb].fork_right = nb;
		check->philos[nb].check = check;
		check->philos[nb].last_eat = check->tstart;
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

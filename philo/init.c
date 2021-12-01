/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:26:47 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/30 22:56:32 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_check(t_check *d, long *param, char **argv)
{
	param[NB_PHILO] = ft_atoi(argv[1]);
	if (param[NB_PHILO] > 200 || param[NB_PHILO] == 0)
	{
		error_msg("numb Philosophers\n");
		return ;
	}
	param[TIME_TO_DIE] = ft_atoi(argv[2]);
	if (param[TIME_TO_DIE] == 0)
	{
		error_msg("Time of death\n");
		return ;
	}
	param[TIME_TO_EAT] = ft_atoi(argv[3]);
	param[TIME_TO_SLEEP] = ft_atoi(argv[4]);
	param[MAX_EAT_COUNT] = -1;
	d->nb_philo_done_eat = 0;
	d->everyone_alive = 1;
	if (argv[5])
		param[MAX_EAT_COUNT] = ft_atoi(argv[5]);
	d->time_start = get_time();
	d->philos = (t_philo *)malloc(sizeof(t_philo) * param[NB_PHILO]);
	if (!d->philos)
	{
		error_msg("Malloc");
		return ;
	}
	d->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param[NB_PHILO]);
	if (!d->forks)
	{
		if (d->philos)
			free(d->philos);
		error_msg("Malloc");
		return ;
	}
}

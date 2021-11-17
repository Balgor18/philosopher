/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 21:42:55 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_fork	*init_forks(int nb_philo)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(*forks) * nb_philo);
	if (forks == NULL)
		return (NULL);
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i-- < 0)
				pthread_mutex_destroy(&forks[i]);
			pthread_mutex_destroy(&forks[i]);
			error_msg("creation forks\n");
			return (NULL);
		}
		++i;
	}
	return (forks);
}

int	philo_init(int *param, t_philo *philo)
{
	t_fork		*forks;
	int			i;

	i = 0;
	forks = init_forks(param[NB_PHILO]);
	if (forks == NULL)
		return (error_msg("Malloc fail\n"));
	printf("Forks init\n");
	philo = malloc(sizeof(t_philo) * param[NB_PHILO]);
	if (!philo)
	{
		free(forks);
		return (error_msg("Malloc fail\n"));
	}
	i = 0;
	while (i < param[NB_PHILO])
	{
		philo[i].param = param;
		// philo[i].forks = forks;
		philo[i].nb = i + 1;
		philo[i].time_prev_eat = 0;
		philo[i].status = PHILO_STATE_THINKING;
		philo[i].already_eat = 0;
		// give_forks(&philosophers[i], forks);
		++i;
	}
	printf("Philo init\n");
	return (TRUE);
}

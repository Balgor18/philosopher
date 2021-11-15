/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/15 11:17:18 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_fork	*forks_init(int nb_philo)
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

int	philo(t_param *param)
{
	t_philo	*philo;
	t_fork	*forks;

	forks = forks_init(param->nb_philo);
	if (forks == NULL)
		return (FALSE);
	if (!create_philo(param, philo))
		return (FALSE);
	return (TRUE);
}

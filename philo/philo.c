/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/16 11:55:14 by fcatinau         ###   ########.fr       */
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

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int	philo_init(t_param *param, t_philo *philo)
{
	t_fork	*forks;
	int		i;

	i = -1;
	while (++i < param->nb_philo)
		philo[i] = (t_philo) {0};
	// philo = (t_philo){0};
	forks = forks_init(param->nb_philo);
	if (forks == NULL)
		return (FALSE);
	printf("Forks init\n");
	// if (!create_philo(param, philo))
	// 	return (FALSE);
	return (TRUE);
}

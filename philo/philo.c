/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/23 22:52:47 by fcatinau         ###   ########.fr       */
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

void	donate_forks(t_philo *philo, t_fork *forks)
{
	t_fork	*left;
	t_fork	*right;

	left = &forks[philo->nb - 1];
	right = &forks[philo->nb % philo->param[NB_PHILO]];
	if (philo->nb % 2 == 0 || philo->nb == philo->param[NB_PHILO])
	{
		philo->fork_right = right;
		philo->fork_left = left;
	}
	else
	{
		philo->fork_right = left;
		philo->fork_left = right;
	}
}

t_philo	*philo_init(int *param, t_philo *philo)
{
	t_fork		*forks;
	int			i;

	i = 0;
	philo = malloc(sizeof(t_philo) * param[NB_PHILO]);
	if (!philo)
	{
		error_msg("Malloc fail\n");
		return (NULL);
	}
	forks = init_forks(param[NB_PHILO]);// !!! do nothing with this forks
	if (forks == NULL)
	{
		free(philo);
		error_msg("Malloc fail\n");
		return (NULL);
	}
	while (i < param[NB_PHILO])
	{
		// philo[i] = (t_philo) {0};// !!! check if need
		philo[i].param = param;
		philo[i].forks = forks;
		philo[i].nb = i + 1;
		philo[i].time_prev_eat = 0;
		philo[i].status = THINKING_STATE;
		philo[i].already_eat = 0;
		donate_forks(&philo[i], forks);
		++i;
	}
	return (philo);
}

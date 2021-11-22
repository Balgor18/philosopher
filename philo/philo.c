/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/22 22:04:18 by fcatinau         ###   ########.fr       */
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

static void	give_forks(t_philo *philo, t_fork *forks)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &forks[philo->id - 1];
	right_fork = &forks[philo->id % philo->params[NB_PHILO]];
	if (philo->id % 2 == 0 || philo->id == philo->params[NB_PHILO])
	{
		philo->first_fork = right_fork;
		philo->second_fork = left_fork;
	}
	else
	{
		philo->first_fork = left_fork;
		philo->second_fork = right_fork;
	}
}

static int	*init_forks_use(int nb_philo)
{
	int	*forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(*forks) * nb_philo);
	if (forks == NULL)
		return (NULL);
	while (i < nb_philo)
	{
		forks[i] = 0;
		++i;
	}
	return (forks);
}

t_philo	*philo_init(int *param, t_philo *philo)
{
	t_fork		*forks;
	int			i;
	int			*fork_use;

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
	fork_use = init_forks_use(param[NB_PHILO]);// !!! do nothing with this forks
	if (fork_use == NULL)
	{
		free(forks);
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
		philo[i].status = PHILO_STATE_THINKING;
		philo[i].already_eat = 0;
		philo[i].fork_use = fork_use;
		// give_forks(&philosophers[i], forks);
		++i;
	}
	// printf("Philo init\n");
	return (philo);
}

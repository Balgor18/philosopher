/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:17:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/29 19:07:46 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_sleep_think(t_check *c, t_philo *philo)
{
	pthread_mutex_lock(&c->forks[philo->fork_right]);
	prompt(c, philo->nb, "has taken a fork");
	pthread_mutex_lock(&c->forks[philo->fork_left]);
	prompt(c, philo->nb, "has taken a fork");
	prompt(c, philo->nb, "is eating");
	pthread_mutex_lock(&philo->lock_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock_eat);
	update_nb_meal(c, philo);
	usleep_opti(c->param[TIME_TO_EAT]);
	pthread_mutex_unlock(&c->forks[philo->fork_right]);
	pthread_mutex_unlock(&c->forks[philo->fork_left]);
	prompt(c, philo->nb, "is sleeping");
	usleep_opti(c->param[TIME_TO_SLEEP]);
	prompt(c, philo->nb, "is thinking");
}

void	*routine(void *thread_philo)
{
	t_philo	*philo;
	t_check	*check;

	philo = (t_philo *)thread_philo;
	check = philo->check;
	// if (pthread_create(&philo->monitor, NULL, &monitor, philo))
	// 	error_msg("Failed to create a thread. (Monitor)");
	if (check->param[NB_PHILO] == 1)
	{
		printf("%u 1 has taken a fork\n", get_time());
		return (NULL);
	}
	while (1)
	{
		if (!check_end_philo(check))
			return (NULL);
		eat_sleep_think(check, philo);
	}
	return (NULL);
}

void	start(t_check *check)
{
	int	nb;

	nb = -1;
	while (++nb < check->param[NB_PHILO])
	{
		if (nb % 2 == 1)
			usleep_opti(5);
		if (pthread_create(&check->philos[nb].thread, NULL, \
		&routine, (void *)&(check->philos[nb])))
			error_msg("Failed to create a thread. (Philos)");
	}
}

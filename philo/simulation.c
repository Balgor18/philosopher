/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:17:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 17:15:10 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(unsigned int ms_time)
{
	unsigned int	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < ms_time)
		usleep(ms_time / 10);
}

void	print(t_check *c, int nb, char *s)
{
	time_t	time;

	pthread_mutex_lock(&c->check_finish);
	pthread_mutex_lock(&c->check_nb_meal);
	if (c->everyone_alive && c->nb_philo_done_eat != c->nb_philo)
	{
		pthread_mutex_lock(&c->is_print);
		time = get_time() - c->tstart;
		printf("%ld %d %s\n", time, nb + 1, s);
		pthread_mutex_unlock(&c->is_print);
	}
	pthread_mutex_unlock(&c->check_nb_meal);
	pthread_mutex_unlock(&c->check_finish);
}

void	eat_sleep_think(t_check *c, t_philo *philo)
{
	pthread_mutex_lock(&c->forks[philo->fork_right]);
	print(c, philo->nb, "has taken a fork");
	pthread_mutex_lock(&c->forks[philo->fork_left]);
	print(c, philo->nb, "has taken a fork");
	print(c, philo->nb, "is eating");
	pthread_mutex_lock(&philo->lock_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock_eat);
	modif_eat(c, philo);
	ft_usleep(c->eat_time);
	pthread_mutex_unlock(&c->forks[philo->fork_right]);
	pthread_mutex_unlock(&c->forks[philo->fork_left]);
	print(c, philo->nb, "is sleeping");
	ft_usleep(c->sleep_time);
	print(c, philo->nb, "is thinking");
}

void	*routine(void *thread_philo)
{
	t_philo	*philo;
	t_check	*check;

	philo = (t_philo *)thread_philo;
	check = philo->check;
	if (pthread_create(&philo->watcher, NULL, &watcher, philo))
		error_msg("Watcher\n");
	if (check->nb_philo == 1)
	{
		printf("%ld 1 has taken a fork\n", get_time() - check->tstart);
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
	while (++nb < check->nb_philo)
	{
		if (nb % 2 == 1)
			ft_usleep(5);
		if (pthread_create(&check->philos[nb].thread, NULL, \
		&routine, (void *)&(check->philos[nb])))
			error_msg("Creation\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:07:17 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 17:48:05 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	modif_eat(t_check *c, t_philo *philo)
{
	pthread_mutex_lock(&c->check_nb_meal);
	philo->nb_eat++;
	// printf("%d == %d\n",philo->nb_eat, c->need_nb_eat);
	if (philo->nb_eat == c->need_nb_eat)
		c->nb_philo_done_eat++;
	pthread_mutex_unlock(&c->check_nb_meal);
}

int	check_end_philo(t_check *c)
{
	pthread_mutex_lock(&c->check_finish);
	pthread_mutex_lock(&c->check_nb_meal);
	// printf("%d || %d == %d && %d\n",c->everyone_alive, c->nb_philo_done_eat, c->nb_philo, c->need_nb_eat);
	if (!c->everyone_alive || \
	(c->nb_philo_done_eat == c->nb_philo
			&& c->need_nb_eat != -1))
	{
		pthread_mutex_unlock(&c->check_nb_meal);
		pthread_mutex_unlock(&c->check_finish);
		return (0);
	}
	pthread_mutex_unlock(&c->check_nb_meal);
	pthread_mutex_unlock(&c->check_finish);
	return (1);
}

int	check_end_monitor(t_check *c, t_philo *philo)
{
	time_t				last_eat;

	pthread_mutex_lock(&philo->lock_eat);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->lock_eat);
	// printf("%llu > %llu\n", get_time() - last_eat, (unsigned long long)c->param[TIME_TO_DIE]);
	if (get_time() - last_eat > c->die_time)
	{
		print(c, philo->nb, "died");
		pthread_mutex_lock(&c->check_finish);
		c->everyone_alive = 0;
		pthread_mutex_unlock(&c->check_finish);
		return (0);
	}
	pthread_mutex_lock(&c->check_nb_meal);
	if (c->nb_philo_done_eat == c->nb_philo)
	{
		pthread_mutex_unlock(&c->check_nb_meal);
		return (0);
	}
	pthread_mutex_unlock(&c->check_nb_meal);
	ft_usleep(5);
	return (1);
}

void	end_simulation(t_check *c)
{
	int	id;

	id = -1;
	while (++id < c->nb_philo)
	{
		pthread_mutex_destroy(&c->forks[id]);
		pthread_mutex_destroy(&c->philos[id].lock_eat);
	}
	pthread_mutex_destroy(&c->is_print);
	pthread_mutex_destroy(&c->check_nb_meal);
	pthread_mutex_destroy(&c->check_finish);
	free(c->philos);
	free(c->forks);
	return ;
}

void	*watcher(void *thread_philo)
{
	t_philo			*philo;
	t_check			*c;

	philo = (t_philo *)thread_philo;
	c = philo->check;
	while (1)
		if (!check_end_monitor(c, philo))
			return (NULL);
	return (NULL);
}

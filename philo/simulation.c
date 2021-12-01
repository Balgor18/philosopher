/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:17:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 01:17:16 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_time	get_time(void)
{
	struct timeval	t;
	t_time	time;

	time = gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

// t_time	time_since_beginning(t_philo *philo)
// {
// 	return (get_time() - philo->start_time);
// }

void	ft_usleep(unsigned int ms_time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < ms_time)
		usleep(ms_time / 10);
}

void	modif_eat(t_check *c, t_philo *philo)
{
	pthread_mutex_lock(&c->check_nb_meal);
	philo->nb_eat++;
	if (philo->nb_eat == c->param[MAX_EAT_COUNT])
		c->nb_philo_done_eat++;
	pthread_mutex_unlock(&c->check_nb_meal);
}

int	check_end_philo(t_check *c)
{
	pthread_mutex_lock(&c->check_finish);
	pthread_mutex_lock(&c->check_nb_meal);
	if (!c->everyone_alive || \
	(c->nb_philo_done_eat == c->param[NB_PHILO]
			&& c->param[MAX_EAT_COUNT] != -1))
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
	if (get_time() - last_eat > (unsigned long long)c->param[TIME_TO_DIE])
	{
		print(c, philo->nb, "died");
		pthread_mutex_lock(&c->check_finish);
		c->everyone_alive = 0;
		pthread_mutex_unlock(&c->check_finish);
		return (0);
	}
	pthread_mutex_lock(&c->check_nb_meal);
	if (c->nb_philo_done_eat == c->param[NB_PHILO])
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
	while (++id < c->param[NB_PHILO])
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

void	print(t_check *c, int nb, char *s)
{
	time_t	time;

	pthread_mutex_lock(&c->check_finish);
	pthread_mutex_lock(&c->check_nb_meal);
	if (c->everyone_alive && c->nb_philo_done_eat != c->param[NB_PHILO])
	{
		pthread_mutex_lock(&c->is_print);
		time = get_time() - c->time_start;
		printf("%ld %d %s\n", time, nb + 1, s);
		pthread_mutex_unlock(&c->is_print);
	}
	pthread_mutex_unlock(&c->check_nb_meal);
	pthread_mutex_unlock(&c->check_finish);
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
	ft_usleep(c->param[TIME_TO_EAT]);
	pthread_mutex_unlock(&c->forks[philo->fork_right]);
	pthread_mutex_unlock(&c->forks[philo->fork_left]);
	print(c, philo->nb, "is sleeping");
	ft_usleep(c->param[TIME_TO_SLEEP]);
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
	if (check->param[NB_PHILO] == 1)
	{
		printf("%llu 1 has taken a fork\n", get_time() - check->time_start);
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
			ft_usleep(5);
		if (pthread_create(&check->philos[nb].thread, NULL, \
		&routine, (void *)&(check->philos[nb])))
			error_msg("Creation\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/26 13:08:52 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static char	*string_per_state(int state)
{
	if (state == 3)
		return (" is thinking");
	else if (state == 2)
		return (" is eating");
	else if (state == 1)
		return (" is sleeping");
	return (" died");
}

void	change_state(t_philo *philo, t_status new_state)
{
	philo->status = new_state;
	if (philo->status == DEAD_STATE)
		*philo->alive = 0;
	ft_print(string_per_state(philo->status), philo->nb, get_time(), 1);
}

static int	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->mutex_alive);
	ft_print(" has taken a fork", philo->nb, get_time(), *philo->alive);
	ft_print(" has taken a fork", philo->nb, get_time(), *philo->alive);
	change_state(philo, EATING_STATE);
	philo->time_prev_eat = get_time();
	if (++philo->already_eat == philo->param[MAX_EAT_COUNT])
	{
		*philo->alive = 0;
		pthread_mutex_unlock(philo->mutex_alive);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	pthread_mutex_unlock(philo->mutex_alive);
	ft_sleep(philo->param[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (1);
}

static void	routine_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_alive);
	change_state(philo, SLEEPING_STATE);
	pthread_mutex_unlock(philo->mutex_alive);
	ft_sleep(philo->param[TIME_TO_SLEEP]);
}

static void	routine_think(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_alive);
	change_state(philo, THINKING_STATE);
	pthread_mutex_unlock(philo->mutex_alive);
}

static int	check_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_alive);
	if (get_time() >= philo->time_prev_eat + philo->param[TIME_TO_DIE])
	{
		change_state(philo, DEAD_STATE);
		*philo->alive = 0;
	}
	if (!*philo->alive)
	{
		pthread_mutex_unlock(philo->mutex_alive);
		return (0);
	}
	pthread_mutex_unlock(philo->mutex_alive);
	return (1);
}

void	*routine(t_philo *philo)
{
	static int	alive = 0;
	pthread_mutex_lock(philo->mutex_alive);
	alive = *philo->alive;
	pthread_mutex_unlock(philo->mutex_alive);
	while (alive == 1)
	{
		// pthread_mutex_unlock(philo->mutex_alive);
		routine_eat(philo);
		// if (!routine_eat(philo))
			// break ;
		if (!check_alive(philo))
			return (philo);
		routine_sleep(philo);
		if (!check_alive(philo))
			return (philo);
		routine_think(philo);
		if (!check_alive(philo))
			return (philo);
		usleep(100);
		pthread_mutex_lock(philo->mutex_alive);
		alive = *philo->alive;
		pthread_mutex_unlock(philo->mutex_alive);
	}
	// pthread_mutex_unlock(philo->mutex_alive);
	return (philo);
}

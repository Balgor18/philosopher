/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/24 23:50:03 by fcatinau         ###   ########.fr       */
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
	pthread_mutex_lock(philo->mutex_alive);
	philo->status = new_state;
	if (philo->status == DEAD_STATE)
		*philo->alive = 0;
	ft_print(string_per_state(philo->status), philo->nb, get_time());
	pthread_mutex_unlock(philo->mutex_alive);
}

static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->mutex_alive);
	ft_print(" has taken a fork", philo->nb, get_time());
	ft_print(" has taken a fork", philo->nb, get_time());
	pthread_mutex_unlock(philo->mutex_alive);
	change_state(philo, EATING_STATE);
	philo->time_prev_eat = get_time();
	if (++philo->already_eat == philo->param[MAX_EAT_COUNT])
	{
		pthread_mutex_lock(philo->mutex_alive);
		*philo->alive = 0;
		pthread_mutex_unlock(philo->mutex_alive);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	ft_sleep(philo->param[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return ;
}

static void	routine_sleep(t_philo *philo)
{
	change_state(philo, SLEEPING_STATE);
	ft_sleep(philo->param[TIME_TO_SLEEP]);
}

static void	routine_think(t_philo *philo)
{
	change_state(philo, THINKING_STATE);
}

void	*routine(t_philo *philo)
{
	int i;

	i = 1;
	while (philo->param[NB_PHILO] == 1 && *philo->alive)
		usleep(100);
	while (*philo->alive == 1)
	{
		routine_eat(philo);
		if (!*philo->alive)
			return (philo);
		routine_sleep(philo);
		if (!*philo->alive)
			return (philo);
		routine_think(philo);
		if (!*philo->alive)
			return (philo);
		// usleep(100);
		i++;
	}
	printf("%d status alive %d\n", philo->nb, *philo->alive);
	printf("============\nje ressorts %d\n============\n", philo->nb);
	return (philo);
}

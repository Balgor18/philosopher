/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 23:18:22 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//state = 3 = think
//state = 2 = eat
//state = 1 = sleep
//state = 0 = dead
static char	*string_per_state(int state)
{
	if (state == 3)
		return ("is thinking");
	else if (state == 2)
		return ("is eating");
	return ("is sleeping");
}

void	change_state(t_philo *philo, t_status new_state)
{
	pthread_mutex_lock(philo->mutex_alive);
	philo->status = new_state;
	ft_print(string_per_state(philo->status), philo->nb, get_time());
	if (philo->status == PHILO_STATE_DEAD)
		philo->alive = FALSE;
	pthread_mutex_unlock(philo->mutex_alive);
}

static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->mutex_alive);
	ft_print(" has taken a fork\n", philo->nb, get_time());
	ft_print(" has taken a fork\n", philo->nb, get_time());
	pthread_mutex_unlock(philo->mutex_alive);
	change_state(philo, PHILO_STATE_EATING);
	philo->time_prev_eat = get_time();
	philo->already_eat++;
	ft_sleep(philo->param[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	routine_sleep(t_philo *philo)
{
	change_state(philo, PHILO_STATE_SLEEPING);
	ft_sleep(philo->param[TIME_TO_SLEEP]);
}

static void	routine_think(t_philo *philo)
{
	change_state(philo, PHILO_STATE_THINKING);
}

void	*routine(t_philo *philo)
{
	while (philo->status)
	{
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
		usleep(100);// check something
	}
	return NULL;
}

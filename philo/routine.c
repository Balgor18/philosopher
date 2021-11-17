/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 12:43:11 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	change_state(t_philo *philo, t_status new_state)
{
	pthread_mutex_lock(philo->out_mutex);
	philo->status = new_state;
	output_status(get_state_string(philo->status), philo);
	if (philo->status == PHILO_STATE_DEAD)
		philo->alive = FALSE;
	pthread_mutex_unlock(philo->out_mutex);
}

static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->out_mutex);
	ft_print(" has taken a fork\n", philo->nb, get_time());
	ft_print(" has taken a fork\n", philo->nb, get_time());
	pthread_mutex_unlock(philo->out_mutex);
	philo_change_state(philo, PHILO_STATE_EATING);
	philo->time_prev_eat = get_timestamp();
	philo->already_eat++;
	ft_sleep(philo->param[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	routine_sleep(t_philo *philo)
{
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_sleep(philo->param[TIME_TO_SLEEP]);
}

static void	philo_routine_think(t_philo *philo)
{
	philo_change_state(philo, PHILO_STATE_THINKING);
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

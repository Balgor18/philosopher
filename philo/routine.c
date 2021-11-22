/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/22 20:00:25 by fcatinau         ###   ########.fr       */
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
		return (" is thinking");
	else if (state == 2)
		return (" is eating");
	return (" is sleeping");
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

static void	get_fork(t_philo *philo, int status)
{
	int	i;
	int	pos;

	pos = 0;
	if (status)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->fork_left = NULL;
		philo->fork_right = NULL;
		while (pos < 2)
		{
			philo->use[pos - 1] = 0;
			pos++;
		}
	}
	else
	{
		while (!philo->fork_left && !philo->fork_right)
		{
			i = 0;
			while (i < philo->param[NB_PHILO])
			{
				if (philo->fork_use[i] == 0)
				{
					if (!philo->fork_left)
						philo->fork_left = &philo->forks[i];
					else if (!philo->fork_right)
						philo->fork_right = &philo->forks[i];
					philo->fork_use[i] = 1;
					philo->use[pos] = i + 1;
					pos++;
				}
				i++;
			}
		}

	}
	return ;
}

static void	routine_eat(t_philo *philo)
{
	// looking for fork ?
	get_fork(philo, 0);// work
	pthread_mutex_lock(philo->fork_left);// !!! can't lock a fork --> need to find a other way
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->mutex_alive);
	ft_print(" has taken a fork", philo->nb, get_time());
	ft_print(" has taken a fork", philo->nb, get_time());
	pthread_mutex_unlock(philo->mutex_alive);
	change_state(philo, PHILO_STATE_EATING);
	philo->time_prev_eat = get_time();
	philo->already_eat++;
	ft_sleep(philo->param[TIME_TO_EAT]);
	dprintf(2, "Enter in get_fork 1\n");
	// get bye fork
	get_fork(philo, 1);// dont work
	dprintf(2, "get out\n");
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
		routine_think(philo);
		routine_eat(philo); // !!! error i don't givefork to philo so i segfault inside this fct
		routine_sleep(philo);
		usleep(100);// check something
	}
	return NULL;
}

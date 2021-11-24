/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/24 17:07:36 by fcatinau         ###   ########.fr       */
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
	ft_print(string_per_state(philo->status), philo->nb, get_time());
	if (philo->status == DEAD_STATE)
		philo->alive = FALSE;
	pthread_mutex_unlock(philo->mutex_alive);
}

static void	routine_eat(t_philo *philo)
{
	// printf("------------\n%d je rentre dans routine eat\n", philo->nb);
	pthread_mutex_lock(philo->fork_left);
	// printf("%d je lock la fourchette\n", philo->nb);
	pthread_mutex_lock(philo->fork_right);
	// printf("%d je lock la fourchette\n", philo->nb);
	pthread_mutex_lock(philo->mutex_alive);
	// printf("%d jai tout lock\n", philo->nb);
	ft_print(" has taken a fork", philo->nb, get_time());
	ft_print(" has taken a fork", philo->nb, get_time());
	pthread_mutex_unlock(philo->mutex_alive);
	change_state(philo, EATING_STATE);
	philo->time_prev_eat = get_time();
	philo->already_eat++;
	// printf("nb_print %d\n", ++nb_print);
	ft_sleep(philo->param[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	// printf("%d je ressor de routine eat\n------------\n", philo->nb);
}

static void	routine_sleep(t_philo *philo)
{
	// printf("============\n%d je rentre dans routine sleep\n", philo->nb);
	change_state(philo, SLEEPING_STATE);
	ft_sleep(philo->param[TIME_TO_SLEEP]);
	// printf("%d je ressors de routine sleep\n============\n", philo->nb);
}

static void	routine_think(t_philo *philo)
{
	// printf("_____________\n%d je rentre dans routine think\n", philo->nb);
	change_state(philo, THINKING_STATE);
	// printf("%d je ressors de routine think\n_____________\n", philo->nb);
}

void	*routine(t_philo *philo)
{
	int i;

	i = 1;
	while (philo->param[NB_PHILO] == 1 && *philo->alive)
		usleep(100);
	while (*philo->alive == 1)
	{
		// printf("je rentre %d\n", philo->nb);
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
		usleep(100);
		// printf("---------\nJe boucle %d\nphilo %d\nalive = %d\n---------\n", i, philo->nb, *philo->alive);
		i++;
	}
	printf("============\nje ressorts %d\n============\n", philo->nb);
	return (philo);
}

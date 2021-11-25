/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:40:19 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/25 14:26:25 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	launch_imp_philo(t_philo *philo)
{
	int	i;
	int	pthread_create_ret;

	i = 1;
	while (i < philo[0].param[NB_PHILO])
	{
		pthread_create_ret = pthread_create(&philo[i].thread, NULL,
				(void *)(void *)&routine, &philo[i]);
		if (pthread_create_ret != 0)
		{
			error_msg("thread create\n");
			return (FALSE);
		}
		i += 2;
	}
	return (TRUE);
}

int	launch_pair_philo(t_philo *philo)
{
	int	i;
	int	pthread_create_ret;

	i = 0;
	while (i < philo[0].param[NB_PHILO])
	{
		pthread_create_ret = pthread_create(&philo[i].thread, NULL,
				(void *)(void *)&routine, &philo[i]);
		if (pthread_create_ret != 0)
		{
			error_msg("thread create\n");
			return (FALSE);
		}
		i += 2;
	}
	return (TRUE);
}

// void	*thread_check_alive(t_philo *philo)
// {
// 	int		i;
// 	// t_philo	*philo_bis;

// 	i = 0;
// 	while (philo->alive)
// 	{
// 		pthread_mutex_lock(philo[i].mutex_alive);
// 		// philo_bis = &philo[i];
// 		if (get_time() >= philo[i].time_prev_eat + philo[i].param[TIME_TO_DIE])
// 			change_state(philo, DEAD_STATE);
// 		if (philo[i].already_eat >= philo[i].param[MAX_EAT_COUNT])
// 			philo[i].alive = FALSE;
// 		else if (i == philo[i].param[NB_PHILO])
// 		{
// 			i = 0;
// 			usleep(100);
// 		}
// 		pthread_mutex_unlock(philo[i].mutex_alive);
// 		i++;
// 	}
// 	philo->alive = FALSE;
// 	return (philo);
// }

static void	launch(t_philo *philo)
{
	// pthread_t			check_philo_dead;
	int i;
	int	nb_philo;
	int	nb_eat;
	int j;

	j = 0;
	i = 0;
	nb_philo = philo[0].param[NB_PHILO];
	nb_eat =  philo[0].param[MAX_EAT_COUNT];;
	// ft_print(NULL, 0, 0);
	if (!launch_imp_philo(philo))
		return ;
	// usleep(1000);
	if (!launch_pair_philo(philo))
		return ;
	// printf("Philo launch \n");
	// printf("alive = %d\n", *philo[0].alive);
	while (i < nb_philo)
	{
		pthread_mutex_lock(philo->mutex_alive);
		if (*philo[i].alive == 0)
		{
			pthread_mutex_unlock(philo->mutex_alive);
			break;
		}
		// if (*philo[i].alive == 2) // check this because not work
		// {
		// 	while (philo[j].already_eat == nb_eat && j < nb_philo)
		// 	{
		// 		j++;
		// 	}
		// 	if (j == nb_philo)
		// 	{
		// 		pthread_mutex_unlock(philo->mutex_alive);
		// 		break;
		// 	}
		// }
		pthread_mutex_unlock(philo->mutex_alive);
		if (++i == nb_philo)
			i = 0;

	}
	i = -1;
	// printf("Je recup tout le monde \n");
	while (++i < nb_philo)
	// {
		pthread_join(philo[i].thread, NULL);
	// }
	// printf("Jai recup tout le monde \n");
}

static int	prelaunch(t_philo *philo)
{
	int				i;
	int				*alive;
	pthread_mutex_t	*mutex_alive;

	mutex_alive = malloc(sizeof(pthread_mutex_t) * 1);
	if (mutex_alive == NULL)
	{
		free(philo->forks);
		free(philo);
		return (error_msg("Malloc fail\n"));
	}
	if (pthread_mutex_init(mutex_alive, 0) != 0)
		return (error_msg("Mutex init fail\n"));
	alive = malloc(sizeof(int) * 1);
	if (alive == NULL)
	{
		free(philo->forks);
		free(philo);
		free(mutex_alive);
		return (error_msg("Malloc fail\n"));
	}
	*alive = TRUE;
	i = 0;
	while (i < philo[0].param[NB_PHILO])
	{
		philo[i].alive = alive;
		philo[i].mutex_alive = mutex_alive;
		++i;
	}
	return (TRUE);
}
int nb_print = 0;
int	main(int argc, char **argv)
{
	t_philo		*philo;
	static int	param[PARAM_MAX];

	philo = NULL;
	param[MAX_EAT_COUNT] = UINT_MAX;
	if (argc >= PARAM_MAX && argc <= PARAM_MAX + 1)
	{
		if (!verif_parse(argc, argv, param))
			return (EXIT_FAILURE);
		philo = philo_init(param, philo);
		if (philo == NULL)
			return (EXIT_FAILURE);
		if (!prelaunch(philo))
			return (EXIT_FAILURE);
		launch(philo);
		return (EXIT_SUCCESS);
	}
	return (error_arg(argc));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:40:19 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/18 18:36:32 by fcatinau         ###   ########.fr       */
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
		printf("pthread_create_ret = %d\n", pthread_create_ret);
		if (pthread_create_ret != 0)
		{
			error_msg("thread create\n");
			return (FALSE);
		}
		i += 2;
	}
	return (TRUE);
}

void	*thread_check_alive(t_philo *philo)
{
	int		i;
	int		full;
	t_philo	*philo_bis;

	full = 0;
	i = 0;
	while (philo[0].alive)
	{
		philo_bis = &philo[i];
		if (get_time() >= philo_bis->time_prev_eat + philo_bis->param[TIME_TO_DIE])
			change_state(philo_bis, PHILO_STATE_DEAD);
		if (philo_bis->already_eat >= philo_bis->param[MAX_EAT_COUNT]
			&& ++full == philo_bis->param[NB_PHILO])
			philo_bis->alive = FALSE;
		else if (++i == philo_bis->param[NB_PHILO])
		{
			full = 0;
			i = 0;
			usleep(1000);
		}
	}
	philo[0].alive = FALSE;
	return (philo);
}

static void	launch(t_philo *philo)
{
	pthread_t			check_philo_dead;

	if (!launch_imp_philo(philo))
		return ;
	printf("Je seg ou\n");
	usleep(1000);
	printf("Je seg ou 2\n");
	if (launch_pair_philo(philo) != 0)
		return ;
	if (pthread_create(&check_philo_dead, NULL,
			(void *)(void *)&thread_check_alive, philo) != 0)
		error_msg("creation thread\n");
	else
		pthread_join(check_philo_dead, NULL);
}

static int	prelaunch(t_philo *philo)
{
	int				i;
	bool			*alive;
	pthread_mutex_t	*mutex_alive;

	mutex_alive = malloc(sizeof(pthread_mutex_t) * 1);
	printf("Je malloc \n");
	if (mutex_alive == NULL)
	{
		free(philo);
		return (error_msg("Malloc fail\n"));
	}
	printf("Init mutex\n");
	if (pthread_mutex_init(mutex_alive, 0) != 0)
		return (error_msg("Mutex init fail\n"));
	alive = malloc(sizeof(bool) * 1);
	printf("Je malloc alive \n");
	if (alive == NULL)
	{
		free(philo);
		free(mutex_alive);
		return (error_msg("Malloc fail\n"));
	}
	printf("Je change la valeur de alive\n");
	*alive = TRUE;
	i = 0;
	printf("Je boucle\n");
	printf("==============\ni = %d\nnb_philo %d\n", i, philo[0].param[NB_PHILO]);
	while (i < philo[0].param[NB_PHILO])
	{
		printf("--------------\ni = %d\n", i);
		philo[i].alive = alive;
		philo[i].mutex_alive = mutex_alive;
		++i;
	}
	printf("Je ressort\n");
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	static int	param[PARAM_MAX];

	philo = NULL;
	if (argc >= PARAM_MAX && argc <= PARAM_MAX + 1)// 5 ou 6
	{
		if (!verif_parse(argc, argv, param))
			return (EXIT_FAILURE);
		philo = philo_init(param, philo);
		if (philo == NULL)
			return (EXIT_FAILURE);
		printf("prelaunch\n");
		if (!prelaunch(philo))
			return (EXIT_FAILURE);
		printf("Launch\n");
		launch(philo);
		return (EXIT_SUCCESS);
	}
	return (error_arg(argc));
}

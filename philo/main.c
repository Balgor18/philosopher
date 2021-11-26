/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:45:08 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/26 15:45:33 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_p				*p;
	t_p				a;
	pthread_mutex_t	*mutex;
	int				i;

	if (ft_arg(&a, ac, av) == FALSE)
		return (1);
	mutex = ft_init_mutex(&a);
	p = ft_init_philo(&a, mutex);
	ft_run(p);
	i = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_destroy(&p[0].mutex[i]);
		i++;
	}
	if (p)
	{
		free(p->dead_mutex);
		free(p->print_mutex);
		free(p);
		p = NULL;
	}
	free(mutex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:13:57 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/13 11:14:06 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_philo(t_param *param, pthread_t *philo)
{
	int	i;

	i = -1;
	while (++i < param->nb_philo)
		if (pthread_create(&philo[i], NULL, &routine, NULL) != 0)
			return (FALSE);
	return (TRUE);
}

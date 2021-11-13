/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/13 11:13:51 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philo(t_param *param, pthread_t *philo)
{
	if (!create_philo(param, philo))
		return (FALSE);
	return (TRUE);
}

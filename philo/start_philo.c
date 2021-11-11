/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:09:24 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 19:27:43 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	start_philo(t_param *param, pthread_t *philo)
{
	(void)param;
	(void)philo;
	printf("%llu", get_time());
	return (TRUE);
}

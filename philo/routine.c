/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/15 10:49:39 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine()
{
	printf("%llu\n", get_time());
	printf("Bonjour ma thread\n");
	sleep(3);
	printf("J'ai finis\n");
	return NULL;
}

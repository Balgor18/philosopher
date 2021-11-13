/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:52:20 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/13 11:10:13 by fcatinau         ###   ########.fr       */
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

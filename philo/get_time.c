/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:29:34 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/13 11:15:20 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;


	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000));
}

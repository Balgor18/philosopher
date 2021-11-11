/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:29:34 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 10:30:08 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint64_t	get_time()
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%llu\n", (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

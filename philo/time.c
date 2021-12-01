/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:12:09 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 23:39:53 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_time	get_time(void)
{
	struct timeval	t;
	t_time			time;

	time = gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

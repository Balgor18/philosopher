/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:29:34 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 14:50:17 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_time	get_time(void)
{
	static t_time	initial = 0;
	t_time			actual;
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	actual = tval.tv_sec * 1000 + tval.tv_usec / 1000;
	if (initial == 0)
		initial = actual;
	return (actual - initial);
}

void	ft_sleep(unsigned long long dur_ms)
{
	t_time	start;
	t_time	actual;
	t_time	end;

	start = get_time();
	end = start + dur_ms;
	while (1)
	{
		actual = get_time();
		if (actual >= end)
			break ;
		usleep(100);
	}
}

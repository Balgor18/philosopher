/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:29:34 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 12:43:19 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_time	get_time(void)
{
	static t_time	initial_ts = 0;
	t_time			current_ts;		
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	current_ts = tval.tv_sec * 1000 + tval.tv_usec / 1000;
	if (initial_ts == 0)
		initial_ts = current_ts;
	return (current_ts - initial_ts);
}

void	ft_msleep(unsigned long long duration_in_ms)
{
	t_time	start_ts;
	t_time	current_ts;
	t_time	end_ts;

	start_ts = get_timestamp();
	end_ts = start_ts + duration_in_ms;
	while (1)
	{
		current_ts = get_timestamp();
		if (current_ts >= end_ts)
			break ;
		usleep(100);
	}
}
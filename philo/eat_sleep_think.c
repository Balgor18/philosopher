/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:57:59 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 16:00:26 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(t_param *param)
{
	usleep(param->time_sleep);
}

void	ft_eat(t_param *param)
{
	usleep(param->time_eat);
}

void	ft_think(t_param *param)
{
	usleep(param->time_eat);
}

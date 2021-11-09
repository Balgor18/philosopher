/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:32:53 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/08 14:58:15 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *c)
{
	int	i;
	int	sign;
	int	total;

	total = 0;
	i = 0;
	sign = 1;
	while ((c[i] >= 9 && c[i] <= 13) || c[i] == ' ')
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			sign *= -1;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		total = total * 10;
		total = total + (c[i] - 48);
		i++;
	}
	return (total * sign);
}

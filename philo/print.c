/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:55:21 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/23 15:49:01 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print(char *s, int nb, t_time time)
{
	// printf("[%lld] %d%s\n", time, nb, s);
	printf("%lld %d%s\n", time, nb, s);
}

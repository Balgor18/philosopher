/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:55:21 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 17:25:09 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print(char *s, int nb, int time)
{
	ft_putchar_fd(STDOUT, '[');
	ft_putnbr_fd(STDOUT, time);
	ft_putstr_fd(STDOUT, "] ");
	ft_putstr_fd(STDOUT, nb);
	ft_putstr_fd(STDOUT, s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:59:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 23:44:16 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	error_msg(char *s)
{
	ft_putstr_fd(STDERR, RED);
	ft_putstr_fd(2, "Error\n");
	ft_putstr_fd(2, WHITE);
	ft_putstr_fd(2, s);
	return (0);
}

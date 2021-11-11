/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:10:59 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 17:11:01 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Fct print Error\n and the message
// Return False = 0
int	error_msg(char *s)
{
	ft_putstr_fd(STDERR, RED"Error\n"WHITE);
	ft_putstr_fd(STDERR, s);
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:59:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/29 15:08:59 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	err_msg(char *s)
(
	ft_putstr_fd(2, RED);
	ft_putstr_fd(2, "Error\n");
	ft_putstr_fd(2, WHITE);
	ft_putstr_fd(2, s);
)

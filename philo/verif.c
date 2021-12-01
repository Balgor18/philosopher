/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:12:07 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/01 23:39:43 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parse_verif_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (FALSE);
	}
	return (SUCCESS);
}

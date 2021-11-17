/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:59:02 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/17 11:13:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

static int	verif_digit(char *s)
{
	if (!*s)
		return (FAILURE);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FAILURE);
		s++;
	}
	return (SUCCESS);
}

int	verif_parse(int argc, char **argv, int *param)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i])
			return (error_msg("Argument empty\n"));
		if (!verif_digit(argv[i]))
			return (error_msg("Argument not a digit\n"));
		if (0 > ft_atoi(argv[i]))
			return (error_msg("Argument negative\n"));
		if (i == 1)
			param[NB_PHILO] = ft_atoi(argv[i]);
		else if (i == 2)
			param[TIME_TO_EAT] = ft_atoi(argv[i]);
		else if (i == 3)
			param[TIME_TO_SLEEP] = ft_atoi(argv[i]);
		else if (i == 4)
			param[MAX_EAT_COUNT] = ft_atoi(argv[i]);
		i++;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:59:02 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/09 13:51:15 by fcatinau         ###   ########.fr       */
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
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FAILURE);
		s++;
	}
	return (SUCCESS);
}

int	parse(int argc, char **argv, t_param *param)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!verif_digit(argv[i]))
			return (FAILURE);
		if (0 < ft_atoi(argv[i]))
			return (FAILURE);
		if (i == 1)
			param->nb_philo = ft_atoi(argv[i]);
		else if (i == 2)
			param->time_eat = ft_atoi(argv[i]);
		else if (i == 3)
			param->time_sleep = ft_atoi(argv[i]);
		else if (i == 4)
			param->many_time_eat = ft_atoi(argv[i]);
		i++;
	}
	return (TRUE);
}

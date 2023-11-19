/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:35:07 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 17:39:04 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_verification(char **str, int ac)
{
	int		i;
	int		j;
	long	nbr;

	i = 1;
	while (i < ac)
	{
		j = 0;
		nbr = ft_atol(str[i]);
		if (nbr <= 0)
			return (-1);
		if (nbr > INT_MAX)
			return (-1);
		if (str[i][j] == '-' || str[i][j] == '+')
			j++;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

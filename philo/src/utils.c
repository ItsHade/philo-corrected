/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:54 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/15 17:50:12 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int			i;
	long int	chaine;
	int			sign;

	i = 0;
	chaine = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		chaine = chaine * 10 + str[i] - '0';
		if (chaine > INT_MAX)
			return (-1);
		i++;
	}
	return (sign * chaine);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start;

	start = ft_get_time();
	while (1)
	{
		if (ft_is_dead(data) == 1)
			break ;
		if ((ft_get_time() - start) >= time)
			break ;
		usleep(1000);
	}
}

void	ft_print_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&(data->write));
	if (ft_is_dead(data) == 0)
	{
		printf("%lld ", (ft_get_time() - data->starting_time));
		printf("%d ", id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(data->write));
}

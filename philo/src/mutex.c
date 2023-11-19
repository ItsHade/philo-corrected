/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:55:36 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/16 19:55:50 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_dead(t_data *data)
{
	pthread_mutex_lock(&(data->dead_check));
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&(data->dead_check));
		return (1);
	}
	pthread_mutex_unlock(&(data->dead_check));
	return (0);
}

int	ft_is_all_ate(t_data *data)
{
	pthread_mutex_lock(&(data->all_ate_check));
	if (data->all_ate == 1)
	{
		pthread_mutex_unlock(&(data->all_ate_check));
		return (1);
	}
	pthread_mutex_unlock(&(data->all_ate_check));
	return (0);
}

void	ft_philo_died(t_data *data, int i)
{
	ft_print_msg(data, i, "died");
	pthread_mutex_lock(&(data->dead_check));
	data->is_dead = 1;
	pthread_mutex_unlock(&(data->dead_check));
}

void	ft_philo_all_ate(t_data *data)
{
	pthread_mutex_lock(&(data->all_ate_check));
	data->all_ate = 1;
	pthread_mutex_unlock(&(data->all_ate_check));
}

void	ft_increment_eat_count(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->eat_count_check));
	(philo->eat_count)++;
	pthread_mutex_unlock(&(data->eat_count_check));
}

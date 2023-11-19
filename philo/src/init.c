/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:25:23 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/19 14:30:47 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

void	ft_initialize_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_nbr;
		data->philo[i].time_last_meal = 0;
		data->philo[i].data = data;
	}
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (-1);
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->write), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->dead_check), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->all_ate_check), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->eat_count_check), NULL))
		return (-1);
	return (0);
}

int	ft_initialize(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->t_t_die = ft_atol(argv[2]);
	data->t_t_eat = ft_atol(argv[3]);
	data->t_t_sleep = ft_atol(argv[4]);
	if (!(data->philo_nbr % 2))
		data->t_think = data->t_t_eat - data->t_t_sleep;
	else
		data->t_think = (data->t_t_eat * 2) - data->t_t_sleep;
	if (argv[5])
		data->nb_of_time_eat = ft_atol(argv[5]);
	else
		data->nb_of_time_eat = -1;
	if (ft_init_mutex(data) == 1)
		return (-1);
	ft_initialize_philo(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:15 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 17:38:34 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_exit(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write));
	pthread_mutex_destroy(&(data->meal_check));
	pthread_mutex_destroy(&(data->dead_check));
	pthread_mutex_destroy(&(data->all_ate_check));
	pthread_mutex_destroy(&(data->eat_count_check));
	ft_free(data);
	return ;
}

int	ft_start(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->is_dead = 0;
	data->all_ate = 0;
	data->starting_time = ft_get_time();
	philo = data->philo;
	if (data->philo_nbr == 1)
	{
		if (pthread_create(&(philo[i].thread_id), NULL,
				philo_do_one, &(philo[i])))
			return (-1);
		return (ft_exit(data, philo), 0);
	}
	while (i < data->philo_nbr)
	{
		philo[i].time_last_meal = ft_get_time();
		if (pthread_create(
				&(philo[i].thread_id), NULL, thread_routine, &(philo[i])))
			return (-1);
		i++;
	}
	return (ft_check_death(data, philo), ft_exit(data, philo), 0);
}


//mettre un limite a 200/250 ??
int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: Arguments invalides\n", 2), -1);
	if (ft_verification(av, ac) == -1)
		return (ft_putstr_fd("Error: Not valid numbers\n", 2), -1);
	if (ft_initialize(&data, av) == -1)
		return (ft_putstr_fd("Error: mutex creation\n", 2), ft_free(&data), -1);
	if (ft_start(&data) == -1)
		return (ft_putstr_fd("Error: thread creation\n", 2), ft_free(&data), -1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:35 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/16 14:01:34 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_do_one(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)v_philo;
	data = philo->data;
	ft_print_msg(data, philo->id, "is thinking");
	ft_usleep(data->t_t_die, data);
	ft_print_msg(data, philo->id, "is dead");
	return (NULL);
}

void	ft_philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		ft_print_msg(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		ft_print_msg(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		ft_print_msg(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		ft_print_msg(data, philo->id, "has taken a fork");
	}
	pthread_mutex_lock(&(data->meal_check));
	ft_print_msg(data, philo->id, "is eating");
	philo->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&(data->meal_check));
	ft_usleep(data->t_t_eat, data);
	ft_increment_eat_count(data, philo);
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	*thread_routine(void *v_philo)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)v_philo;
	data = philo->data;
	ft_print_msg(data, philo->id, "is thinking");
	if (philo->id % 2 == 0)
			ft_usleep(data->t_t_eat / 10, data);
	while (ft_is_dead(data) == 0)
	{
		ft_philo_eat(philo);
		if (data->nb_of_time_eat != -1 && philo->eat_count >= data->nb_of_time_eat)
			break ; 
		ft_print_msg(data, philo->id, "is sleeping");
		ft_usleep(data->t_t_sleep, data);
		ft_print_msg(data, philo->id, "is thinking");
		usleep(100);
		i++;
	}
	return (NULL);
}

int	ft_eat_count(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&(data->eat_count_check));
	if (philo[i].eat_count < data->nb_of_time_eat)
	{
		pthread_mutex_unlock(&(data->eat_count_check));
		return (1);
	}
	pthread_mutex_unlock(&(data->eat_count_check));
	return (0);
}

void	ft_check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (ft_is_all_ate(data) == 0)
	{
		i = -1;
		while (++i < data->philo_nbr && ft_is_dead(data) == 0)
		{
			pthread_mutex_lock(&(data->meal_check));
			if (ft_get_time() - philo[i].time_last_meal > data->t_t_die)
				ft_philo_died(data, i);
			pthread_mutex_unlock(&(data->meal_check));
			usleep(data->t_t_die / 2);
		}
		if (ft_is_dead(data) == 1)
			break ;
		i = 0;
		while (data->nb_of_time_eat != -1 && i < data->philo_nbr)
		{
			if (ft_eat_count(data, philo, i) == 1)
				break ;
			i++;
		}
		if (i == data->philo_nbr)
			ft_philo_all_ate(data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:33:19 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/15 17:49:43 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				eat_count;
	long long		time_last_meal;
	int				right_fork;
	int				left_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long int		philo_nbr;
	long int		t_t_die;
	long int		t_t_eat;
	long int		t_t_sleep;
	long int		nb_of_time_eat;
	int				is_dead;
	int				all_ate;
	long long		starting_time;
	long int		t_think;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	dead_check;
	pthread_mutex_t	all_ate_check;
	pthread_mutex_t	eat_count_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			*philo;
}	t_data;

/* INIT */

void		ft_initialize_philo(t_data *data);

int			ft_init_mutex(t_data *data);

int			ft_initialize(t_data *data, char **argv);

void		ft_free(t_data *data);

/* PUT FUNCTIONS */

void		ft_putchar(char c);

void		ft_putstr(char *str);

void		ft_putstr_fd(char *str, int fd);

void		ft_putnbr(int nb);

/* THREADS */

int			ft_start(t_data *data);

void		*thread_routine(void *data);

void		*philo_do_one(void *v_philo);

void		ft_exit(t_data *data, t_philo *philo);

void		ft_check_death(t_data *data, t_philo *philo);

/* PHILO UTILS */

long long	ft_get_time(void);

void		ft_print_msg(t_data *data, int id, char *msg);

void		ft_usleep(long long time, t_data *data);

/* MUTEX */

int			ft_is_dead(t_data *data);

void		ft_philo_died(t_data *data, int i);

int			ft_is_all_ate(t_data *data);

void		ft_philo_all_ate(t_data *data);

void		ft_increment_eat_count(t_data *data, t_philo *philo);

/* UTILS */

int			ft_isdigit(int c);

long		ft_atol(const char *str);

/* ARGS */

int			ft_verification(char **str, int ac);

#endif

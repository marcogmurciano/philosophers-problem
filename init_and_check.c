/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:35:51 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:37:57 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_a_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	init_data(t_data *data, char **av)
{
	data->philo_n = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	data->must_eat = -1;
	if (av[5])
		data->must_eat = atoi(av[5]);
}

static void	init_array(t_philo **philo_arr, int i, t_data *data)
{
	(*philo_arr)[i].data = data;
	(*philo_arr)[i].index = i;
	(*philo_arr)[i].is_satisfied = 0;
	(*philo_arr)[i].is_alive = 1;
	(*philo_arr)[i].has_own_fork = 0;
	(*philo_arr)[i].has_borrowed_fork = 0;
	pthread_mutex_init(&((*philo_arr)[i].is_alive_mutex), NULL);
	pthread_mutex_init(&((*philo_arr)[i].is_satisfied_mutex), NULL);
	pthread_mutex_init(&((*philo_arr)[i].last_meal_mutex), NULL);
}

int	inicialize_philos(t_philo **philo_arr, pthread_mutex_t **mutex_arr,
		t_data *data, char **av)
{
	int	i;

	if (error_check(av))
		return (1);
	init_data(data, av);
	*philo_arr = malloc(sizeof(t_philo) * data->philo_n);
	data->action = 1;
	pthread_mutex_init(&(data->action_mutex), NULL);
	i = 0;
	while (i < data->philo_n)
	{
		init_array(philo_arr, i, data);
		i++;
	}
	*mutex_arr = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	i = -1;
	while (++i < data->philo_n)
		pthread_mutex_init(&((*mutex_arr)[i]), NULL);
	return (0);
}

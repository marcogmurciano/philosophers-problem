/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ 
/*   Created: 2025/08/23 15:30:06 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:45:41 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*supervising(void *philos)
{
	t_philo	*philo_arr;
	int		satisfied_philos;
	int		i;
	int		stop_status;

	philo_arr = *((t_philo **)philos);
	stop_status = 0;
	satisfied_philos = 0;
	while (1)
	{
		i = -1;
		while (++i < philo_arr[0].data->philo_n)
		{
			if (get_timestamp(philo_arr[i].data->timestamp_start)
				- philo_arr[i].last_meal >= philo_arr[i].data->t_die)
			{
				stop_status += i + 1;
				pthread_mutex_lock(&(philo_arr[0].data->action_mutex));
				philo_arr[0].data->action = 0;
				pthread_mutex_unlock(&(philo_arr[0].data->action_mutex));
			}
			if (satisfied_philos >= philo_arr[i].data->philo_n)
				stop_status += 1000;
		}
		if (stop_status != 0)
			break;
	}
	//grito de muerte (i - 1 es el indice del filosofo)
	i = stop_status % 1000;
	if (i > 0)
		print_msg(i - 1, "died", philo_arr[0].data);
	//debug
	if ((i / 1000) == 1)
		printf("satisfacción!!!\n");
	//muerte y destrucción
	pthread_mutex_lock(&(philo_arr[0].data->action_mutex));
	philo_arr[0].data->action = 0;
	pthread_mutex_unlock(&(philo_arr[0].data->action_mutex));
	i = -1;
	while (++i < philo_arr[0].data->philo_n)
	{
		pthread_mutex_lock(&philo_arr[i].is_alive_mutex);
		// printf("MATAR A %d\n", i + 1);
		philo_arr[i].is_alive = 0;
		pthread_mutex_unlock(&philo_arr[i].is_alive_mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo			*philo_arr;
	t_data			data;
	pthread_mutex_t	*mutex_arr;
	pthread_t		supervisor;
	int				i;

	if (ac < 4 || inicialize_philos(&philo_arr, &mutex_arr, &data, av))
		return (printerror());
	data.timestamp_start = get_time();
	data.mutex_arr = mutex_arr;
	if (data.philo_n == 1)
		return (one_philosopher(&(philo_arr[0])));
	pthread_create(&(supervisor), NULL, supervising, &(philo_arr));
	i = -1;
	while (++i < data.philo_n)
		pthread_create(&(philo_arr[i].tid), NULL, philosophing,
			&(philo_arr[i]));
	i = -1;
	while (++i < data.philo_n)
		pthread_join((philo_arr[i].tid), NULL);
	i = -1;
	while (++i < data.philo_n)
		pthread_mutex_destroy(&(mutex_arr[i]));
	//
	for (int i = 0; i < data.philo_n; i++) {
		pthread_mutex_destroy(&philo_arr[i].is_alive_mutex);
		pthread_mutex_destroy(&philo_arr[i].is_satisfied_mutex);
		pthread_mutex_destroy(&philo_arr[i].last_meal_mutex);
		pthread_mutex_destroy(&mutex_arr[i]);
	}
	pthread_mutex_destroy(&data.action_mutex);
	//
	return (0);
}

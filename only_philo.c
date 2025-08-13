/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:36:40 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:37:03 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*only_philo(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	pthread_mutex_lock(&(philo->data->mutex_arr[0]));
	philo->has_own_fork = 1;
	printf("%ld: [Hilo %d] has taken a fork\n",
		get_timestamp(philo->data->timestamp_start), philo->index);
	misleep(philo->data->t_die);
	philo->has_own_fork = 0;
	pthread_mutex_unlock(&(philo->data->mutex_arr[0]));
	printf("%ld: [Hilo %d] died\n", get_timestamp(philo->data->timestamp_start),
		philo->index);
	return (NULL);
}

int	one_philosopher(t_philo *philo)
{
	pthread_create(&(philo->tid), NULL, only_philo, philo);
	pthread_join((philo->tid), NULL);
	return (0);
}

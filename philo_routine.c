/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:30:06 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:39:35 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_forks(t_philo *philo, int right)
{
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_unlock(&philo->is_alive_mutex);
	pthread_mutex_lock(&(philo->data->mutex_arr[philo->index]));
	philo->has_own_fork = 1;
	print_msg(philo->index + 1, "Has taken a fork", philo->data);
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_unlock(&philo->is_alive_mutex);
	pthread_mutex_lock(&(philo->data->mutex_arr[right]));
	philo->has_borrowed_fork = 1;
	print_msg(philo->index + 1, "Has taken a fork", philo->data);
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_unlock(&philo->is_alive_mutex);
	return (1);
}

static int	ingest(t_philo *philo)
{
	print_msg(philo->index + 1, "Is eating", philo->data);
	misleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_unlock(&philo->is_alive_mutex);
	return (1);
}

static int	drop_forks(t_philo *philo, int right, int i)
{
	if (i == philo->data->must_eat)
	{
		print_msg(philo->index + 1, "SARTISFECHO", philo->data);
		pthread_mutex_lock(&philo->is_satisfied_mutex);
		philo->is_satisfied = 1;
		pthread_mutex_unlock(&philo->is_satisfied_mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp(philo->data->timestamp_start);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo->has_own_fork = 0;
	pthread_mutex_unlock(&(philo->data->mutex_arr[philo->index]));
	philo->has_borrowed_fork = 0;
	pthread_mutex_unlock(&(philo->data->mutex_arr[right]));
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_unlock(&philo->is_alive_mutex);
	misleep(philo->data->t_sleep);
	return (1);
}

static void	*death_scream(t_philo *philo, int right)
{
	if (philo->has_own_fork)
		pthread_mutex_unlock(&(philo->data->mutex_arr[philo->index]));
	if (philo->has_borrowed_fork)
		pthread_mutex_unlock(&(philo->data->mutex_arr[right]));
	return (NULL);
}

void	*philosophing(void *philo_data)
{
	t_philo	*philo;
	int		i;
	int		right;

	i = 0;
	philo = (t_philo *)philo_data;
	right = (philo->index - 1 + (philo->data->philo_n)) % (philo->data->philo_n);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = philo->data->timestamp_start;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (philo->index % 2 == 0)
		misleep(25);
	while (1)
	{
////////////////////////////
		pthread_mutex_lock(&(philo->data->action_mutex));
		if (philo->data->action)
		{
			if (!get_forks(philo, right))
				break ;
		}
		pthread_mutex_unlock(&(philo->data->action_mutex));
////////////////////////////
		pthread_mutex_lock(&(philo->data->action_mutex));
		if (philo->data->action)
		{
			if (!ingest(philo))
				break ;
			i++;
		}
		pthread_mutex_unlock(&(philo->data->action_mutex));
////////////////////////////
		pthread_mutex_lock(&(philo->data->action_mutex));
		if (philo->data->action)
		{
			if (!drop_forks(philo, right, i))
				break ;
		}
		pthread_mutex_unlock(&(philo->data->action_mutex));
////////////////////////////
		pthread_mutex_lock(&(philo->data->action_mutex));
		if (philo->data->action)
			print_msg(philo->index + 1, "Is thinking", philo->data);
		pthread_mutex_unlock(&(philo->data->action_mutex));
	}
	pthread_mutex_unlock(&(philo->data->action_mutex));
	return (death_scream(philo, right));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:30:52 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:40:22 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct data_s
{
	int				philo_n;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				action;
	long			timestamp_start;
	pthread_mutex_t	*mutex_arr;
	pthread_mutex_t	action_mutex;
}					t_data;

typedef struct philo_s
{
	pthread_t		tid;
	int				index;
	int				is_satisfied;
	int				is_alive;
	int				has_borrowed_fork;
	int				has_own_fork;
	long			last_meal;
	t_data			*data;
	pthread_mutex_t	is_satisfied_mutex;
	pthread_mutex_t	is_alive_mutex;
	pthread_mutex_t	last_meal_mutex;
}					t_philo;

int		one_philosopher(t_philo *philo);
void	*supervising(void *philos);
void	*only_philo(void *philo_data);
int		is_a_number(char *str);
int		error_check(char **av);
int		inicialize_philos(t_philo **philo_arr, pthread_mutex_t **mutex_arr,
			t_data *data, char **av);
int		printerror(void);
long	get_time(void);
long	get_timestamp(long start);
void	misleep(int d);
void	*philosophing(void *philo_data);
void	print_msg(int id, char *msg, t_data *data);
int		is_dead(t_philo *philo);

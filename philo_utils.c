/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-29 08:50:48 by user              #+#    #+#             */
/*   Updated: 2025-08-29 08:50:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_number(char *str)
{
	char	*p;

	p = str;
	if (!str || !*str)
		return (0);
	while (*p == ' ')
		p++;
	if (*p == '-' || *p == '+')
		p++;
	if (!isdigit((unsigned char)*p))
		return (0);
	while (*p)
	{
		if (!isdigit((unsigned char)*p))
			return (0);
		p++;
	}
	if (atoi(str) <= 0)
		return (0);
	return (1);
}

int	printerror(void)
{
	printf("\n[ERROR] Argumentos inválidos.\nUso correcto:\n"
		"    ./philo <time_to_die> <time_to_eat> <time_to_sleep> \
		[times_each_philo_must_eat]\n\n"
		"Detalles de los argumentos:\n"
		"  - Todos los valores deben ser números enteros positivos.\n"
		"  - No se permiten números negativos, ceros,\
		ni caracteres no numéricos.\n"
		"  - El argumento 'times_each_philo_must_eat' es opcional.\n"
		"Ejemplo:\n    ./philo 800 200 200 7\n");
	return (1);
}

int	is_dead(t_philo *philo)
{
	if (!(philo->is_alive))
	{
		pthread_mutex_unlock(&philo->is_alive_mutex);
		return (1);
	}
	return (0);
}

void	print_msg(int id, char *msg, t_data *data)
{
	long timestamp;

	timestamp = get_timestamp(data->timestamp_start);
	printf("%ld: [Philo %d] %s...\n", timestamp, id, msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:12 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/23 15:38:56 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	misleep(int d)
{
	usleep(d * 1000);
}

long	get_timestamp(long start)
{
	long			actual;
	long			result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	actual = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	result = actual - start;
	return (result);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

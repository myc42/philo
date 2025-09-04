/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_and_write_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:05:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/04 21:42:32 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_ms(void)
{
	struct timeval	x;

	gettimeofday(&x, NULL);
	return ((x.tv_sec * 1000) + (x.tv_usec / 1000));
}

void	start_delay(long start_time)
{
	while (get_time_ms() > start_time )
		usleep(100);
}

void	write_status(t_data *data, t_philo *philo, const char *message)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->philosopher_died)
		return (pthread_mutex_unlock(&data->death_mutex), (void)0);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", get_time_ms() - data->simulation_start_time, philo->id, message);
	pthread_mutex_unlock(&data->print_mutex);
}
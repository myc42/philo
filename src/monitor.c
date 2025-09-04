/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:00:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/04 20:24:17 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		req;
	long	time_since_last_meal;

	data = (t_data *)arg;
	while (1)
	{
		req = 1;
		i = 0;
		while (i < data->total_philosophers)
		{
			pthread_mutex_lock(&data->philosophers[i].meal_time_lock);
			time_since_last_meal = get_time_ms()
				- data->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&data->philosophers[i].meal_time_lock);
			if (time_since_last_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->philosopher_died = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d has died\n", get_time_ms() - data->simulation_start_time, i);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			if (data->required_meals > 0
				&& data->philosophers[i].meals_eaten < data->required_meals)
				req = 0;
			i++;
		}
		if (req && data->required_meals > 0)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->all_met_requirements = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(200);
	}
}

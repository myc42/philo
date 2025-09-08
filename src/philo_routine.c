/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:40:33 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/05 17:53:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_rt(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->shared_data->time_to_die - (get_time_ms()
				- philo->last_meal_time) - philo->shared_data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		philo_sleep(philo->shared_data, time_to_think);
}

void	philo_sleep(t_data *data, long time_in_ms)
{
	long	start;

	start = get_time_ms();
	while (!simulation_stopped(data) && get_time_ms() - start < time_in_ms)
		usleep(200);
}

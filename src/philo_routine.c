/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:40:33 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/04 21:46:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_data *data, long time_in_ms)
{
	long	start;

	start = get_time_ms();
	while (!simulation_stopped(data) && get_time_ms() - start < time_in_ms)
		usleep(100);
}

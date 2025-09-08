/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/05 18:38:18 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanall(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < data->total_philosophers)
		pthread_mutex_destroy(&data->fork_mutexes[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->fork_mutexes);
	free(data->philosophers);
	free(data);
}

int	create_thread(t_data *data)

{
	int i;

	i = 0;
	while (i < data->total_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, philo_routine,
				&data->philosophers[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
		return (1);
	i = 0;
	while (i < data->total_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data *data;
	data = NULL;

	if (ac != 5 && ac != 6)
		return (printf("Usage: ./philo nb_philo t_die t_eat t_sleep [must_eat]\n"),
			1);
	data = init_data(ac, av);
	if (!data)
		return (1);
	if (create_thread(data) != 0)
		return (cleanall(data), 1);
	cleanall(data);
	return (0);
}
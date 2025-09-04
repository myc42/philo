/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:38 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/04 21:36:03 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->shared_data->total_philosophers;
	if (philo->id % 2 == 0)
	{
		philo->fork[0] = right;
		philo->fork[1] = left;
	}
	else
	{
		philo->fork[0] = left;
		philo->fork[1] = right;
	}
}

int	rest_and_mutexes_init(t_data *data)
{
	int	i;

	data->philosopher_died = 0;
	data->simulation_start_time = get_time_ms();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < data->total_philosophers)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_time = data->simulation_start_time;
		data->philosophers[i].shared_data = data;
		if(pthread_mutex_init(&data->philosophers[i].meal_time_lock, NULL) != 0)
			return (0);
		take_fork(&data->philosophers[i]);
		i++;
	}
	return (1);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->required_meals = ft_atoi(av[5]);
	else
		data->required_meals = -1;
	if (data->total_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (ac == 6
			&& data->required_meals <= 0))
		return (NULL);
	data->fork_mutexes = malloc(sizeof(pthread_mutex_t)
			* data->total_philosophers);
	data->philosophers = malloc(sizeof(t_philo) * data->total_philosophers);
	if (!data->philosophers || !data->fork_mutexes)
		return (NULL);
	if (!rest_and_mutexes_init(data) || !init_philo(data))
		return (NULL);
	return (data);
}

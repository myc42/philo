/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:35 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/05 18:09:45 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	valid_argv(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (j < ac)
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		if (ft_atoi(av[i]) < 0)
			return (1);
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (2);
	return (0);
}

int	simulation_stopped(t_data *data)
{
	int stopped;

	pthread_mutex_lock(&data->death_mutex);
	stopped = (data->philosopher_died || data->all_met_requirements);
	pthread_mutex_unlock(&data->death_mutex);
	return (stopped);
}
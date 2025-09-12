/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:35 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/10 15:59:52 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (nb > INT_MAX)
			return (-1);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((int)nb);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	valid_argv(int ac, char **av)
{
	int	i;
	int	j;
	int	val;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		val = ft_atoi(av[i]);
		if (val < 1)
			return (1);
		if (i == 1 && val > 200)
			return (1);
		i++;
	}
	return (0);
}

int	simulation_stopped(t_data *data)
{
	int	stopped;

	stopped = 0;
	pthread_mutex_lock(&data->death_mutex);
	stopped = (data->philosopher_died || data->all_met_requirements);
	pthread_mutex_unlock(&data->death_mutex);
	return (stopped);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:32 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/09 23:43:42 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long				simulation_start_time;
	int					total_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	int					required_meals;
	int					philosopher_died;
	int					all_met_requirements;
	pthread_mutex_t		*fork_mutexes;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_t			monitor_thread;
	t_philo				*philosophers;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	t_data				*shared_data;
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
}						t_philo;

void					*philo_routine(void *x);
void					take_fork(t_philo *philo);
void					start_delay(long start_time);
void					philo_sleep(t_data *data, long time_in_ms);
int						rest_and_mutexes_init(t_data *data);
int						init_philo(t_data *data);
int						valid_argv(int ac, char **av);
int						ft_atoi(char *str);
int						simulation_stopped(t_data *data);
t_data					*init_data(int ac, char **av);
void					write_status(t_data *data, t_philo *philo,
							const char *message);
time_t					get_time_ms(void);
void					*monitor_routine(void *x);
void					think_rt(t_philo *philo, bool silent);

#endif
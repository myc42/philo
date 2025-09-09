/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:12:32 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/09 20:12:01 by macoulib         ###   ########.fr       */
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

// structure
typedef struct s_philo	t_philo;

typedef struct s_data
{
	long simulation_start_time;    // Moment où la simulation commence
	int total_philosophers;        // Nombre total de philosophes
	int time_to_die;               // Temps maximal sans manger avant de mourir
	int time_to_eat;               // Durée de l'action manger
	int time_to_sleep;             // Durée de l'action dormir
	int time_to_think;             // Durée de l'action dormir
	int required_meals;            // Nbr de repas requis pour chaque philosophe
	int philosopher_died;          // Indique si un philosophe est mort (bool)
	int all_met_requirements;      // ls philosophes ont atteint le nbr de repas
	pthread_mutex_t *fork_mutexes; // Tableau de mutex pour les fourchettes
	pthread_mutex_t print_mutex;   // Mutex pour l'affichage
	pthread_mutex_t death_mutex;   // Mutex pour vérifier la mort
	pthread_mutex_t meal_mutex;    // Mutex pour accéder aux repas
	pthread_t monitor_thread;      // Thread de surveillance
	t_philo *philosophers;         // Tableau des philosophes
}						t_data;

typedef struct s_philo
{
	pthread_t thread;    // Thread associé au philosophe
	t_data *shared_data; // Pointeur vers les données partagées
	int id;              // Identifiant du philosophe
	int meals_eaten;     // Nombre de repas consommés
	long last_meal_time; // Heure du dernier repas
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
}						t_philo;

// functions

void					*philo_routine(void *x);
void					take_fork(t_philo *philo);
int						rest_and_mutexes_init(t_data *data);
int						init_philo(t_data *data);
t_data					*init_data(int ac, char **av);
void					write_status(t_data *data, t_philo *philo,
							const char *message);
time_t					get_time_ms(void);
void					start_delay(long start_time);
void					philo_sleep(t_data *data, long time_in_ms);
int						simulation_stopped(t_data *data);
void					*monitor_routine(void *x);
int						valid_argv(int ac, char **av);
int						ft_atoi(char *str);
void					think_rt(t_philo *philo, bool silent);

#endif
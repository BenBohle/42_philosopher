/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:11:51 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/23 15:31:56 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"
#include "../includes/stylesheet.h"

void init_specs(t_specs *specs, int n_philos) {
    specs->n_philos = n_philos;
    specs->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
    for (int i = 0; i < n_philos; i++) {
        pthread_mutex_init(&specs->forks[i], NULL);
    }
    pthread_mutex_init(&specs->lock, NULL);
    specs->stop = 0;
}

void init_philosophers(t_philo *philos, t_specs *specs, int n_philos) {
    for (int i = 0; i < n_philos; i++) {
        philos[i].id = i;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % n_philos;
        philos[i].n_eaten = 0;
        philos[i].last_meal = get_current_time();
        philos[i].specs = specs;
    }
}

void init_simulation(int argc, char **argv, t_specs *specs, t_philo **philos) {
    if (check_input(argc, argv) == 1) 
        start_screen();
    
    init_specs(specs, atoi(argv[1]));
    specs->time_to_die = atoi(argv[2]);
    specs->time_to_eat = atoi(argv[3]);
    specs->time_to_sleep = atoi(argv[4]);
    if (argc == 6) {
        specs->n_to_eat = atoi(argv[5]);
    } else {
        specs->n_to_eat = -1;
    }
    pthread_mutex_init(&specs->stop_mutex, NULL);

    *philos = malloc(specs->n_philos * sizeof(t_philo));
    init_philosophers(*philos, specs, specs->n_philos);
}

void create_philosopher_threads(t_philo *philos, t_specs *specs, pthread_t *threads) {
    int counter;

	counter = 0;
	while (counter < specs->n_philos) {
		pthread_create(&threads[counter], NULL, philosopher_routine, &philos[counter]);
		counter++;
	}
}

void create_monitor_thread(pthread_t *monitor_thread, t_philo *philos) {
    if (pthread_create(monitor_thread, NULL, monitoring, philos) != 0) {
		perror("Failed to create watcher thread");
		// Fehlerbehandlung
	}
}
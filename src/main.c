/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:20:49 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/23 16:09:17 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"


void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_specs *specs = philo->specs;

    while (1) {

		pthread_mutex_lock(&specs->stop_mutex);
		int stop = specs->stop;
		pthread_mutex_unlock(&specs->stop_mutex);
		if (stop == 1) {
			break;
		}

        // Denken
        print_status(philo->id, "is thinking", specs);
		if (specs->n_philos == 1) {
			better_usleep(specs->time_to_die);
			break;
		}

        // Gabeln nehmen
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(&specs->lock);
            pthread_mutex_lock(&specs->forks[philo->left_fork]);
            print_status(philo->id, "has taken a fork", specs);
            pthread_mutex_lock(&specs->forks[philo->right_fork]);
            print_status(philo->id, "has taken a fork", specs);
            pthread_mutex_unlock(&specs->lock);
        } else {
			better_usleep(1);
            pthread_mutex_lock(&specs->forks[philo->right_fork]);
            print_status(philo->id, "has taken a fork", specs);
            pthread_mutex_lock(&specs->forks[philo->left_fork]);
            print_status(philo->id, "has taken a fork", specs);
        }

        // Essen
        print_status(philo->id, "is eating", specs);
        // philo->last_meal = get_current_time();
        better_usleep(specs->time_to_eat);
		philo->last_meal = get_current_time();
		if (specs->n_to_eat != -1)
        	philo->n_eaten++;

        // Gabeln zurücklegen
        pthread_mutex_unlock(&specs->forks[philo->right_fork]);
        pthread_mutex_unlock(&specs->forks[philo->left_fork]);

        // Schlafen
        print_status(philo->id, "is sleeping", specs);
        better_usleep(specs->time_to_sleep);

        // Häufigere Überprüfung des Todeszustands
        // better_usleep(100); // 1 ms Pause zwischen den Überprüfungen
    }

    return NULL;
}

int main(int argc, char **argv) {
    t_specs specs;
	t_philo *philos;
    pthread_t *threads;
    pthread_t monitor_thread;
	int counter;

	init_simulation(argc, argv, &specs, &philos);
	threads = malloc(specs.n_philos * sizeof(pthread_t));
	create_philosopher_threads(philos, &specs, threads);
	create_monitor_thread(&monitor_thread, philos);

	counter = 0;
	while (counter < specs.n_philos) {
		pthread_join(threads[counter], NULL);
		counter++;
	}

	// Warten auf das Ende des Überwachungsthreads
	if (pthread_join(monitor_thread, NULL) != 0) {
		perror("Failed to join watcher thread");
		// Fehlerbehandlung
	}

	counter = 0;
	while (counter < specs.n_philos) {
		pthread_mutex_destroy(&specs.forks[counter]);
		counter++;
	}
	pthread_mutex_destroy(&specs.lock);
	pthread_mutex_destroy(&specs.stop_mutex);
	free(philos);
	free(threads);
	free(specs.forks);
	

    return 0;
}

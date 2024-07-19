/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:11:51 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/19 15:11:54 by bbohle           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:40:20 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/19 17:14:46 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

void *monitoring(void *arg) {
    t_philo *philo = (t_philo *)arg;
	t_specs *specs = philo->specs;
    int counter;
    long current_time;

    while (1) {
        counter = 0;
        while (counter < specs->n_philos) {
            current_time = get_current_time();
            if (current_time - philo[counter].last_meal > specs->time_to_die) {
                pthread_mutex_lock(&specs->stop_mutex);
				specs->stop = 1;
				print_status_dead(counter, "died");
				pthread_mutex_unlock(&specs->stop_mutex);
                return NULL;
            }
            counter++;
        }
        usleep(10);
    }

    return NULL;
}
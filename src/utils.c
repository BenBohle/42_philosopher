/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:12:04 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/19 15:16:15 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

long get_current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void better_usleep(int microseconds) {
    struct timeval start, current;
    gettimeofday(&start, NULL);
    long elapsed = 0;

    while (elapsed < microseconds) {
        // usleep(100); // Optional: Kurzes Schlafen für Effizienz, hier auskommentiert
        gettimeofday(&current, NULL);
        elapsed = (current.tv_sec - start.tv_sec) * 1000000 + (current.tv_usec - start.tv_usec);
    }
}
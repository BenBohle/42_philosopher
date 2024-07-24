/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:23:48 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 01:34:55 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

int InitController(int argc, char **argv, t_specs specs, t_philo philos) {
	if (init_simulation(argc, argv, &specs, &philos) == EXIT_FAILURE)
	{
		printf("Error initializing simulation\n");
		return (EXIT_FAILURE);
	}
	return 0;
}

int CreateController(t_specs *specs, t_philo *philos, pthread_t *threads, pthread_t *monitor_thread) {
	
	if (create_philosopher_threads(philos, &specs, threads) == EXIT_FAILURE)
	{
		printf("Error creating philosopher threads\n");
		return (EXIT_FAILURE);
	}
	if (create_monitor_thread(&monitor_thread, philos) == EXIT_FAILURE)
	{
		printf("Error creating monitor thread\n");
		return (EXIT_FAILURE);
	}
	if (join_threads(threads, specs.n_philos, &monitor_thread) == EXIT_FAILURE)
	{
		printf("Error joining threads\n");
		return (EXIT_FAILURE);
	}
	return 0;
}
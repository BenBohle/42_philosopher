/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:11:51 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 01:45:22 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

int	init_specs(t_specs *specs, int n_philos)
{
	int	counter;

	specs->n_philos = n_philos;
	specs->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!specs->forks)
	{
		printf("Error allocating memory for forks\n");
		return (EXIT_FAILURE);
	}
	counter = 0;
	while (counter < n_philos)
	{
		pthread_mutex_init(&specs->forks[counter], NULL);
		counter++;
	}
	pthread_mutex_init(&specs->lock, NULL);
	specs->stop = 0;
	return (0);
}

void	init_philosophers(t_philo *philos, t_specs *specs, int n_philos)
{
	int	counter;

	counter = 0;
	while (counter < n_philos)
	{
		philos[counter].id = counter;
		philos[counter].left_fork = counter;
		philos[counter].right_fork = (counter + 1) % n_philos;
		philos[counter].n_eaten = 0;
		philos[counter].last_meal = get_current_time();
		philos[counter].specs = specs;
		counter++;
	}
}

int	init_simulation(int argc, char **argv, t_specs *specs, t_philo **philos)
{
	if (init_specs(specs, atoi(argv[1])) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	specs->time_to_die = atoi(argv[2]);
	specs->time_to_eat = atoi(argv[3]);
	specs->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
	{
		specs->n_to_eat = atoi(argv[5]);
	}
	else
	{
		specs->n_to_eat = -1;
	}
	specs->start_time = get_current_time();
	pthread_mutex_init(&specs->stop_mutex, NULL);
	*philos = malloc(specs->n_philos * sizeof(t_philo));
	if (!*philos)
		return (EXIT_FAILURE);
	init_philosophers(*philos, specs, specs->n_philos);
	return (0);
}

int	create_philosopher_threads(t_philo *philos, t_specs *specs,
		pthread_t *threads)
{
	int	counter;

	counter = 0;
	while (counter < specs->n_philos)
	{
		if (pthread_create(&threads[counter], NULL, philosopher_routine,
				&philos[counter]) != 0)
		{
			printf("Error creating philosopher thread\n");
			return (EXIT_FAILURE);
		}
		counter++;
	}
	return (0);
}

int	create_monitor_thread(pthread_t *monitor_thread, t_philo *philos)
{
	if (pthread_create(monitor_thread, NULL, monitoring, philos) != 0)
	{
		printf("Error creating monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

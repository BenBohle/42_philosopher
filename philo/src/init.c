/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:11:51 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 19:17:25 by bbohle           ###   ########.fr       */
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
	// pthread_mutex_init(&specs->lock, NULL);
	pthread_mutex_lock(&specs->stop_mutex);
	specs->stop = 0;
	pthread_mutex_unlock(&specs->stop_mutex);
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
	pthread_mutex_init(&specs->stop_mutex, NULL);
	if (init_specs(specs, ft_atoi(argv[1])) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	specs->time_to_die = ft_atoi(argv[2]);
	specs->time_to_eat = ft_atoi(argv[3]);
	specs->time_to_sleep = ft_atoi(argv[4]);
	specs->eaten_philos = 0;
	specs->stop = 0;
	if (argc == 6)
	{
		specs->n_to_eat = ft_atoi(argv[5]);
	}
	else
	{
		specs->n_to_eat = -1;
	}
	specs->start_time = get_current_time();
	
	*philos = malloc(specs->n_philos * sizeof(t_philo));
	if (!*philos)
		return (cleanup(specs), EXIT_FAILURE);
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

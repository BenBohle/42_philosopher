/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:20:49 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 19:01:27 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

void	cleanup(t_specs *specs)
{
	int	counter;

	counter = 0;
	while (counter < specs->n_philos)
	{
		pthread_mutex_destroy(&specs->forks[counter]);
		counter++;
	}
	// pthread_mutex_destroy(&specs->lock);
	pthread_mutex_destroy(&specs->stop_mutex);
	free(specs->forks);
}

int	join_threads(pthread_t *threads, int n_philos,
		pthread_t *monitor_thread)
{
	int	counter;

	counter = 0;
	while (counter < n_philos)
	{
		pthread_join(threads[counter], NULL);
		counter++;
	}
	if (pthread_join(*monitor_thread, NULL) != 0)
	{
		printf("Error joining monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

void print_mutex_addresses(t_specs *specs, t_philo *philos, int n_philos)
{
    printf("Address of n_philos: %p\n", (void *)&specs->n_philos);
    printf("Address of n_forks: %p\n", (void *)&specs->n_forks);
    printf("Address of time_to_die: %p\n", (void *)&specs->time_to_die);
    printf("Address of time_to_eat: %p\n", (void *)&specs->time_to_eat);
    printf("Address of time_to_sleep: %p\n", (void *)&specs->time_to_sleep);
    printf("Address of n_to_eat: %p\n", (void *)&specs->n_to_eat);
    printf("Address of eaten_philos: %p\n", (void *)&specs->eaten_philos);
    printf("Address of forks: %p\n", (void *)&specs->forks);
    printf("Address of stop: %p\n", (void *)&specs->stop);
    printf("Address of start_time: %p\n", (void *)&specs->start_time);
    printf("Address of stop_mutex: %p\n", (void *)&specs->stop_mutex);

    for (int i = 0; i < n_philos; i++)
    {
        printf("Address of left_fork for philosopher %d: %p\n", i, (void *)&specs->forks[philos[i].left_fork]);
    }
}

int	main(int argc, char **argv)
{
	t_specs		specs;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;

	if (check_input(argc, argv) == 1)
		start_screen();
	if (is_n_to_eat_zero(argc, argv) == 1 || check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	if (init_controller(argc, argv, &specs, &philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	threads = malloc(specs.n_philos * sizeof(pthread_t));
	if (threads == NULL)
	{
		printf("Failed to allocate memory for threads\n");
		return (cleanup(&specs), EXIT_FAILURE);
	}
	print_mutex_addresses(&specs, philos, specs.n_philos);

	if (create_controller(&specs, philos,
			threads, &monitor_thread) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	print_mutex_addresses(&specs, philos, specs.n_philos);

	cleanup(&specs);
	free(philos);
	free(threads);
	return (0);
}

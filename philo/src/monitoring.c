/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:40:20 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 15:55:04 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

int	death_condition(t_philo *philo, t_specs *specs, int counter)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time - philo[counter].last_meal > specs->time_to_die)
	{
		pthread_mutex_lock(&specs->stop_mutex);
		specs->stop = 1;
		print_status_dead(counter, "died", specs);
		pthread_mutex_unlock(&specs->stop_mutex);
		return (1);
	}
	return (0);
}

int	eat_condition(t_philo *philo, t_specs *specs, int counter)
{
	if (specs->n_to_eat != -1 && philo[counter].n_eaten == specs->n_to_eat + 1)
	{
		specs->eaten_philos++;
	}
	if (specs->eaten_philos == specs->n_philos)
	{
		pthread_mutex_lock(&specs->stop_mutex);
		specs->stop = 1;
		pthread_mutex_unlock(&specs->stop_mutex);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	t_specs	*specs;
	int		counter;

	philo = (t_philo *)arg;
	specs = philo->specs;
	while (1)
	{
		counter = 0;
		while (counter < specs->n_philos)
		{
			if (death_condition(philo, specs, counter))
				return (NULL);
			if (eat_condition(philo, specs, counter) == 1)
				return (NULL);
			counter++;
		}
		usleep(10);
	}
	return (NULL);
}

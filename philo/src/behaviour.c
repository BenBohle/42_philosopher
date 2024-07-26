/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:51:09 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 19:23:29 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

void	take_forks(t_philo *philo, t_specs *specs)
{
	if (philo->id % 2 == 0)
	{
		// pthread_mutex_lock(&specs->lock);
		pthread_mutex_lock(&specs->forks[philo->left_fork]);
		print_status(philo->id, "has taken a fork", specs);
		pthread_mutex_lock(&specs->forks[philo->right_fork]);
		print_status(philo->id, "has taken a fork", specs);
		// pthread_mutex_unlock(&specs->lock);
	}
	else
	{
		better_usleep(1);
		pthread_mutex_lock(&specs->forks[philo->right_fork]);
		print_status(philo->id, "has taken a fork", specs);
		pthread_mutex_lock(&specs->forks[philo->left_fork]);
		print_status(philo->id, "has taken a fork", specs);
	}
}

void	eat(t_philo *philo, t_specs *specs)
{
	print_status(philo->id, "is eating", specs);
	better_usleep(specs->time_to_eat);
	philo->last_meal = get_current_time();
	if (specs->n_to_eat != -1)
		philo->n_eaten++;
}

void	put_forks_back(t_philo *philo, t_specs *specs)
{
	pthread_mutex_unlock(&specs->forks[philo->right_fork]);
	pthread_mutex_unlock(&specs->forks[philo->left_fork]);
}

void	sleep_philo(t_philo *philo, t_specs *specs)
{
	print_status(philo->id, "is sleeping", specs);
	better_usleep(specs->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_specs	*specs;
	int		stop;

	philo = (t_philo *)arg;
	specs = philo->specs;
	while (1)
	{
		pthread_mutex_lock(&specs->stop_mutex);
		stop = specs->stop;
		pthread_mutex_unlock(&specs->stop_mutex);
		if (stop == 1)
			break ;
		print_status(philo->id, "is thinking", specs);
		if (specs->n_philos == 1)
		{
			better_usleep(specs->time_to_die);
			break ;
		}
		take_forks(philo, specs);
		eat(philo, specs);
		put_forks_back(philo, specs);
		sleep_philo(philo, specs);
	}
	return (NULL);
}

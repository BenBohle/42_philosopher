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
	int		time_since_last_meal;

	if (specs->n_philos % 2 == 1)
	{
		pthread_mutex_lock(&specs->lock);
		time_since_last_meal = get_current_time() - philo->last_meal;
		pthread_mutex_unlock(&specs->lock);
		if ((specs->time_to_die - time_since_last_meal)
			/ 4 < specs->time_to_eat)
			better_usleep(specs->time_to_eat);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&specs->forks[philo->left_fork]);
		print_status(philo->id, "has taken a fork", specs);
		pthread_mutex_lock(&specs->forks[philo->right_fork]);
		print_status(philo->id, "has taken a fork", specs);
	}
	else
	{
		pthread_mutex_lock(&specs->forks[philo->right_fork]);
		print_status(philo->id, "has taken a fork", specs);
		pthread_mutex_lock(&specs->forks[philo->left_fork]);
		print_status(philo->id, "has taken a fork", specs);
	}
}

void	eat(t_philo *philo, t_specs *specs)
{
	print_status(philo->id, "is eating", specs);
	pthread_mutex_lock(&specs->lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&specs->lock);
	better_usleep(specs->time_to_eat);
	pthread_mutex_lock(&specs->lock);
	if (specs->n_to_eat != -1)
		philo->n_eaten++;
	pthread_mutex_unlock(&specs->lock);
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
	if (philo->id % 2 == 1)
		better_usleep(specs->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&specs->stop_mutex);
		stop = specs->stop;
		pthread_mutex_unlock(&specs->stop_mutex);
		if (stop == 1)
			break ;
		print_status(philo->id, "is thinking", specs);
		if (is_one_philo(specs))
			break ;
		take_forks(philo, specs);
		eat(philo, specs);
		put_forks_back(philo, specs);
		sleep_philo(philo, specs);
	}
	return (NULL);
}

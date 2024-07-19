/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:17:56 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/19 17:22:26 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_specs
{

    int long long n_philos;
    int long long n_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int n_to_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t lock;
    int stop;
	pthread_mutex_t stop_mutex;

} t_specs;

typedef struct s_philo
{
    int id;
    int left_fork;
    int right_fork;
    int n_eaten;
    long last_meal;
    t_specs *specs;
} t_philo;

int main(int argc, char **argv);
void init_philosophers(t_philo *philos, t_specs *specs, int n_philos);
void init_specs(t_specs *specs, int n_philos);
void *philosopher_routine(void *arg);
long get_current_time();
void better_usleep(int microseconds);
void *monitoring(void *arg);
int check_input(int argc, char **argv);


#endif
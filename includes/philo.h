/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:17:56 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 19:08:40 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_specs
{
	int long long	n_philos;
	int long long	n_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_to_eat;
	int				eaten_philos;
	pthread_mutex_t	*forks;
	int				stop;
	long			start_time;
	pthread_mutex_t	stop_mutex;

}					t_specs;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				n_eaten;
	long			last_meal;
	t_specs			*specs;
}					t_philo;

int					main(int argc, char **argv);
int					join_threads(pthread_t *threads, int n_philos,
						pthread_t *monitor_thread);
void				cleanup(t_specs *specs);

void				*monitoring(void *arg);

int					init_simulation(int argc, char **argv, t_specs *specs,
						t_philo **philos);
void				init_philosophers(t_philo *philos, t_specs *specs,
						int n_philos);
int					init_specs(t_specs *specs, int n_philos);
int					create_philosopher_threads(t_philo *philos, t_specs *specs,
						pthread_t *threads);
int					create_monitor_thread(pthread_t *monitor_thread,
						t_philo *philos);

int					init_controller(int argc, char **argv, t_specs *specs,
						t_philo **philos);
int					create_controller(t_specs *specs, t_philo *philos,
						pthread_t *threads, pthread_t *monitor_thread);

int					check_input(int argc, char **argv);
int					is_n_to_eat_zero(int argc, char **argv);
int					is_not_number(char *str);

void				better_usleep(int time);
long				get_current_time(void);

void				*philosopher_routine(void *arg);
void				sleep_philo(t_philo *philo, t_specs *specs);
void				put_forks_back(t_philo *philo, t_specs *specs);
void				eat(t_philo *philo, t_specs *specs);
void				take_forks(t_philo *philo, t_specs *specs);

int ft_atoi(const char *str);
int ft_atoicheck(char c);

#endif
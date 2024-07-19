/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:40:15 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/19 17:15:28 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/philo.h"
#include "../includes/stylesheet.h"

void start_screen()
{
	
printf("\n██████╗ ██╗  ██╗██╗" YELLOW "██" RESET "╗      ██████╗\n");
printf(YELLOW "██" RESET "╔══██╗██║  ██║██║██║     ██╔═══██╗\n");
printf("██████╔╝███████║"YELLOW "██" RESET "║██║     ██║   ██║\n");
printf("██╔═══╝ ██╔══██║██║██║     " YELLOW "██" RESET "║   ██║\n");
printf("██║     " YELLOW "██" RESET "║  ██║██║███████╗╚██████╔╝\n");
printf("╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝\n\n"); 
                                    

}

void wrong_input()
{
	printf(RED BOLD "Error: Invalid arguments\n\n" RESET);
	printf(UNDERLINE "Usage:" RESET " ./philo " MAGENTA "[" RESET "number_of_philosophers" MAGENTA "]" RESET 
			" " MAGENTA "[" RESET "time_to_die" MAGENTA "] ["  RESET "time_to_eat" MAGENTA "]" RESET 
			" " MAGENTA "[" RESET "time_to_sleep" MAGENTA "]" RESET 
			" " MAGENTA "[" RESET "number_of_times_each_philosopher_must_eat" MAGENTA "]" RESET "\n\n");
	exit(1);
}

void print_status(int id, const char *status, t_specs *specs) {
    long timestamp = get_current_time();
	pthread_mutex_lock(&specs->stop_mutex);
    int stop = specs->stop;
    pthread_mutex_unlock(&specs->stop_mutex);
	if (stop == 0)
	{
		printf("%ld %d %s\n", timestamp, id, status);
	}
}

void print_status_dead(int id, const char *status) {
	long timestamp = get_current_time();
	printf("%ld %d %s\n", timestamp, id, status);
}
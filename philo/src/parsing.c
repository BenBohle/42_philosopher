/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:21:12 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 16:47:17 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

int	is_not_number(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] < '0' || str[counter] > '9')
			return (1);
		counter++;
	}
	return (0);
}

int	is_n_to_eat_zero(int argc, char **argv)
{
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (1);
	return (0);
}

int	is_max_int(char *str)
{
	long	num;

	num = ft_atoll(str);
	if (num > INT_MAX || num < INT_MIN)
		return (1);
	return (0);
}

int	is_philo_zero(char *str)
{
	if (ft_atoi(str) == 0)
		return (1);
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	counter;

	if (argc < 5 || argc > 6)
	{
		return (1);
	}
	counter = 1;
	while (counter != argc)
	{
		if (is_philo_zero(argv[counter]) == 1)
			return (1);
		if (is_not_number(argv[counter]) == 1)
			return (1);
		if (is_max_int(argv[counter]) == 1)
			return (1);
		counter++;
	}
	return (0);
}

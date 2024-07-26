/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:12:04 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 16:22:34 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

int ft_strlen(char *str)
{
	int counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	better_usleep(int microseconds)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < microseconds)
	{
		usleep(100);
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_atoicheck(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f')
	{
		return (1);
	}
	else if (c == '+' || c == '-')
	{
		return (2);
	}
	else if (ft_isdigit(c) == 1)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

int	ft_atoi(const char *str)
{
	int		counter;
	int		number;
	char	minusplus;

	counter = 0;
	number = 0;
	minusplus = 0;
	while (ft_atoicheck(str[counter]) >= 1 && minusplus == 0)
	{
		if (ft_atoicheck(str[counter]) == 2)
		{
			minusplus = str[counter];
		}
		counter++;
	}
	while (ft_isdigit(str[counter]) == 1)
	{
		number = number * 10 + (str[counter] - 48);
		counter++;
	}
	if (minusplus == '-')
		return (-number);
	return (number);
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& *str - '0' > LLONG_MAX % 10))
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

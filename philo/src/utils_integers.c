/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:06:19 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/27 17:06:52 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/stylesheet.h"

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

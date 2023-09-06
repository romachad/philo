/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:12:31 by romachad          #+#    #+#             */
/*   Updated: 2023/09/06 03:47:02 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	check_negative(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (-2);
		else
			return (-1);
	}
	else if (n == 0)
		return (0);
	else
		return (1);
}

static int	size_n(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*allocate(int signal, int digits)
{
	char	*str;

	if (signal < 0)
	{
		str = malloc((digits + 2) * sizeof(char));
		if (!str)
			return (0);
		str[digits + 1] = 0;
	}
	else
	{
		str = malloc((digits + 1) * sizeof(char));
		if (!str)
			return (0);
		str[digits] = 0;
	}
	return (str);
}

static char	*get_number(int signal, int n, int flag)
{
	char	*number;
	int		digits;

	if (signal == -2)
		n = (n + 1) * -1;
	else if (signal == -1)
		n = n * -1;
	digits = size_n(n);
	number = allocate(signal, digits);
	if (!number)
		return (0);
	while (digits > 0)
	{
		number[digits - flag] = 0x30 + (n % 10);
		if (signal == -2)
		{
			signal = -1;
			number[digits]++;
		}
		n = n / 10;
		digits--;
	}
	if (signal < 0)
		number[0] = '-';
	return (number);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		signal;

	signal = check_negative(n);
	if (signal == 0)
	{
		number = malloc(2 * sizeof(char));
		if (number)
		{
			number[0] = 0x30;
			number[1] = 0;
			return (number);
		}
		else
			return (0);
	}
	else
	{
		if (signal < 0)
			return (get_number(signal, n, 0));
		else
			return (get_number(signal, n, 1));
	}
}

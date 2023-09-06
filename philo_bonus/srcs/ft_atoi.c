/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:05:29 by romachad          #+#    #+#             */
/*   Updated: 2023/08/26 18:58:14 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static char	*skip_spaces(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ' && str[i] != '\f' && str[i] != '\n')
			if (str[i] != '\r' && str[i] != '\t' && str[i] != '\v')
				return ((char *) &str[i]);
		i++;
	}
	return ((char *) str);
}

static int	check_signal_number(char c)
{
	if (c == '+' || (c >= '0' && c <= '9'))
		return (1);
	else if (c == '-')
		return (-1);
	else
		return (0);
}

static unsigned int	get_numbers(char *str)
{
	size_t			i;
	size_t			j;
	unsigned int	nb;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	nb = 0;
	j = 0;
	while (j < i && str[j] >= '0' && str[j] <= '9')
	{
		nb = (nb * 10) + (str[j] - 0x30);
		j++;
	}
	return (nb);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	nb;
	int				signal;
	char			*new_addr;

	if (!nptr)
		return (0);
	new_addr = skip_spaces(nptr);
	signal = check_signal_number(new_addr[0]);
	if (!signal)
		return (0);
	else
	{
		if (new_addr[0] == '-' || new_addr[0] == '+')
			new_addr++;
		nb = get_numbers(new_addr);
		if (signal == -1)
			return (nb * signal);
		else
			return (nb);
	}
}

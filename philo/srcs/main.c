/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:14:31 by romachad          #+#    #+#             */
/*   Updated: 2023/08/26 19:24:21 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (printf("philo: wrong number of arguments!\n"));
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(isdigit(argv[i][j])))
				return (printf("philo: "\
						"Arguments must be positve numbers only!\n"));
		}
	}
	if (ft_atoi(argv[1]) < 1)
		return (printf("philo: there must be at least one philo!\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) != 0)
		return (1);
	else
		return (0);
}

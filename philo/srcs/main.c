/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:14:31 by romachad          #+#    #+#             */
/*   Updated: 2023/09/01 05:33:47 by romachad         ###   ########.fr       */
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
	if (argc == 6)
		if (ft_atoi(argv[5]) < 1)
			return (printf("Number of meals must be one or greater\n"));
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	else
		return (time.tv_sec * (uint64_t)1000000 + time.tv_usec);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv) != 0)
		return (1);
	init(&table, argc, argv);
	table.philos = malloc(table.simulation.n_philos * sizeof(t_philo));
	load(&table);
	create_threads(&table);
	return (0);
}

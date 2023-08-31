/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:14:31 by romachad          #+#    #+#             */
/*   Updated: 2023/08/30 23:10:09 by romachad         ###   ########.fr       */
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

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	else
		//return (time.tv_sec * (uint64_t)1000 + (time.tv_usec / 1000));
		return (time.tv_sec * (uint64_t)1000000 + time.tv_usec);
}

int	main(int argc, char **argv)
{
	//uint64_t	start;
	//uint64_t	end;
	t_table	table;
	
	//printf("40: %d\n41: %d\n44: %d\n45: %d\n46: %d\n49: %d\n", 40/10, 41/10, 44/10, 45/10, 46/10, 49/10);


	if (check_args(argc, argv) != 0)
		return (1);
	//else
	//	return (0);
	
	
	/*start = get_time();
	usleep(10000);
	end = get_time();
	printf("Exec time: %ld\n", end - start);*/

	init(&table, argc, argv);

	printf("start time: %ld\n", table.simulation.t_start);
	table.philos = malloc(table.simulation.n_philos * sizeof(t_philo));
	//table.philos = malloc(2 * sizeof(t_philo));
	load(&table);
	create_threads(&table);


	return (0);
}

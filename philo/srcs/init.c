/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:56:00 by romachad          #+#    #+#             */
/*   Updated: 2023/08/29 06:13:18 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init(t_table *table, int argc, char **argv)
{
	table->simulation.n_philos = ft_atoi(argv[1]);
	table->simulation.t_die = (ft_atoi(argv[2]) * 1000);
	table->simulation.t_eat = (ft_atoi(argv[3]) * 1000);
	table->simulation.t_sleep = (ft_atoi(argv[4]) * 1000);
	table->simulation.max_eat = -1;
	if (argc == 6)
		table->simulation.max_eat = ft_atoi(argv[5]);
	table->simulation.t_start = get_time(); //move this to after ready to start threads;
}


void	load(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->simulation.n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].count_eat = 0;
		table->philos[i].t_last_eat = table->simulation.t_start;
		pthread_mutex_init(&table->philos[i].fork, NULL);
		// if ONLY ONE PHILO!!! IMPLEMENTAR AQUI
		if (i > 0)
		{
			table->philos[i - 1].n_fork = &table->philos[i].fork;
			if (i == table->simulation.n_philos - 1)
				table->philos[i].n_fork = &table->philos[0].fork;
		}
	}
}


void	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->simulation.n_philos)
	{
		table->philos[i].sim = &table->simulation;
		pthread_create(&table->philos[i].p_thread, NULL, &thread_cicle, &table->philos[i]);
	}
	i = -1;
	while (++i < table->simulation.n_philos)
	{
		pthread_join(table->philos[i].p_thread, NULL);
	}
}

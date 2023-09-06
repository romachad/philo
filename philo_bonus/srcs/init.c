/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:56:00 by romachad          #+#    #+#             */
/*   Updated: 2023/09/06 04:57:14 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init(t_table *table, int argc, char **argv)
{
	table->simulation.n_philos = ft_atoi(argv[1]);
	table->simulation.t_die = (ft_atoi(argv[2]) * 1000);
	table->simulation.t_eat = (ft_atoi(argv[3]) * 1000);
	table->simulation.t_sleep = (ft_atoi(argv[4]) * 1000);
	table->simulation.is_dead = 0;
	table->simulation.d_thread = 0;
	table->simulation.race = 0;
	table->simulation.forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, table->simulation.n_philos);
	table->simulation.print = sem_open("/print", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (table->simulation.n_philos > 2 && table->simulation.n_philos % 2 == 1)
		table->simulation.race = 1;
	table->simulation.global_turn = 0;
	table->simulation.max_eat = -1;
	if (argc == 6)
		table->simulation.max_eat = ft_atoi(argv[5]);
}

void	load_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->simulation.n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].count_eat = 0;
		table->philos[i].t_last_eat = table->simulation.t_start;
		table->philos[i].turn = i % 2;
		if (table->philos[i].id == table->simulation.n_philos \
				&& table->simulation.n_philos % 2 == 1)
			table->philos[i].turn = 2;
		table->philos[i].l_race = table->simulation.race;
		/*pthread_mutex_init(&table->philos[i].fork, NULL);
		if (i > 0 && table->simulation.n_philos > 1)
		{
			table->philos[i - 1].n_fork = &table->philos[i].fork;
			if (i == table->simulation.n_philos - 1)
				table->philos[i].n_fork = &table->philos[0].fork;
		}*/
	}
}

/*void	load(t_table *table)
{
	pthread_mutex_init(&table->simulation.control_eat, NULL);
	pthread_mutex_init(&table->simulation.control_death, NULL);
	pthread_mutex_init(&table->simulation.print, NULL);
	pthread_mutex_init(&table->simulation.end, NULL);
	pthread_mutex_init(&table->simulation.c_turn, NULL);
	load_philos(table);
}*/

/*static void	wait_death_threads(t_table *table)
{
	int	local_d_thread;

	local_d_thread = 0;
	pthread_mutex_lock(&table->simulation.end);
	local_d_thread = table->simulation.d_thread;
	pthread_mutex_unlock(&table->simulation.end);
	while (local_d_thread > 0)
	{
		usleep(5000);
		pthread_mutex_lock(&table->simulation.end);
		local_d_thread = table->simulation.d_thread;
		pthread_mutex_unlock(&table->simulation.end);
	}
}*/

//void	create_threads(t_table *table)
void	create_pids(t_table *table)
{
	int	i;

	table->simulation.pid = malloc(table->simulation.n_philos * sizeof(int));
	table->simulation.t_start = get_time();
	i = -1;
	while (++i < table->simulation.n_philos)
	{
		table->philos[i].sim = &table->simulation;
		table->simulation.pid[i] = fork();
		if (table->simulation.pid[i] == 0)
			philo_pid(table, i);
	}
	i = -1;
	while (++i < table->simulation.n_philos)
		waitpid(table->simulation.pid[i], NULL, 0);
	free(table->simulation.pid);
	sem_close(table->simulation.forks);
	sem_unlink("/forks"); 
	free(table->philos);
	

	/*if (table->simulation.n_philos > 1)
	{
		i = -1;
		while (++i < table->simulation.n_philos)
		{
			table->philos[i].sim = &table->simulation;
			table->philos[i].t_last_eat = get_time();
			pthread_create(&table->philos[i].p_thread, \
					NULL, &thread_cicle, &table->philos[i]);
		}
	}
	else
		single_philo(table);
	i = -1;
	while (++i < table->simulation.n_philos)
		pthread_join(table->philos[i].p_thread, NULL);
	wait_death_threads(table);
	pthread_mutex_destroy(&table->simulation.control_eat);
	pthread_mutex_destroy(&table->simulation.control_death);
	pthread_mutex_destroy(&table->simulation.print);
	pthread_mutex_destroy(&table->simulation.end);
	free(table->philos);*/
}

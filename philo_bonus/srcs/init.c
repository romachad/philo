/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:56:00 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 05:14:52 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

//void	init(t_table *table, int argc, char **argv)
void	init(t_sim *simulation, int argc, char **argv)
{
	simulation->n_philos = ft_atoi(argv[1]);
	simulation->t_die = (ft_atoi(argv[2]) * 1000);
	simulation->t_eat = (ft_atoi(argv[3]) * 1000);
	simulation->t_sleep = (ft_atoi(argv[4]) * 1000);
	simulation->is_dead = 0;
	simulation->d_thread = 0;
	simulation->race = 0;
	simulation->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, simulation->n_philos);
	simulation->print = sem_open("/print", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	simulation->can_eat = sem_open("/can_eat", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, simulation->n_philos / 2);
	//if (table->simulation.n_philos > 2 && table->simulation.n_philos % 2 == 1)
	//	table->simulation.race = 1;
	//table->simulation.global_turn = 0;
	simulation->max_eat = -1;
	if (argc == 6)
		simulation->max_eat = ft_atoi(argv[5]);
}

/*void	load_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->simulation.n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].count_eat = 0;
		//table->philos[i].turn = i % 2;
		//if (table->philos[i].id == table->simulation.n_philos \
				&& table->simulation.n_philos % 2 == 1)
			//table->philos[i].turn = 2;
		//table->philos[i].l_race = table->simulation.race;
	}
}*/

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
//void	create_pids(t_table *table)
void	create_pids(t_sim *simulation)
{
	int	i;
	//char *str;
	t_philo	philo;

	simulation->pid = malloc(simulation->n_philos * sizeof(int));
	simulation->t_start = get_time();
	philo.t_last_eat = simulation->t_start;
	philo.sim = simulation;
	philo.count_eat = 0;
	i = -1;
	//while (++i < table->simulation.n_philos)
	while (++i < simulation->n_philos)
	{
		//table->philos[i].t_last_eat = table->simulation.t_start;
		//table->philos[i].sim = &table->simulation;
		philo.id = i + 1;
		simulation->pid[i] = fork();
		if (simulation->pid[i] == 0)
			//philo_pid(table, i);
			philo_pid(&philo);
		//else
			//sem_close(table->philos[i].control_death);
	}
	i = -1;
	while (1)
	{
		int pid_end;
		int status;
		int exit_s;
		pid_end = waitpid(-1, &status, WNOHANG);
		if (pid_end > 0)
		{
			if (WIFEXITED(status)){
				exit_s = WEXITSTATUS(status);
			}
			else
				exit_s = -1;
			printf("Esse cabou: %d , status: %d\n", pid_end, exit_s);
			i = -1;
			while (++i < simulation->n_philos)
			{
				if (simulation->pid[i] != pid_end)
				{
					//printf("vou matar: %d, id: %d\n", table->simulation.pid[i], table->philos[i].id);
					kill(simulation->pid[i], SIGKILL);
				}
				//sem_unlink(table->philos[i].philo_n);
				//free(table->philos[i].philo_n);
			}
			//printf("matei todos?\n");
			//usleep(30000000);
			break ;
		}
	}
	free(simulation->pid);
	sem_close(simulation->forks);
	sem_close(simulation->print);
	sem_close(simulation->can_eat);
	sem_unlink("/forks"); 
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/can_eat");
	//free(table->philos);
	

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

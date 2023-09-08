/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:56:00 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 06:24:53 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init(t_sim *simulation, int argc, char **argv)
{
	simulation->n_philos = ft_atoi(argv[1]);
	simulation->t_die = (ft_atoi(argv[2]) * 1000);
	simulation->t_eat = (ft_atoi(argv[3]) * 1000);
	simulation->t_sleep = (ft_atoi(argv[4]) * 1000);
	simulation->forks = sem_open("/forks", \
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, simulation->n_philos);
	simulation->print = sem_open("/print", \
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	simulation->can_eat = sem_open("/can_eat", \
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, simulation->n_philos / 2);
	simulation->max_eat = -1;
	if (argc == 6)
		simulation->max_eat = ft_atoi(argv[5]);
}

void	create_pids(t_sim *simulation)
{
	t_philo	philo;
	int		i;

	simulation->pid = malloc(simulation->n_philos * sizeof(int));
	simulation->t_start = get_time();
	philo.t_last_eat = simulation->t_start;
	philo.sim = simulation;
	philo.count_eat = 0;
	i = -1;
	while (++i < simulation->n_philos)
	{
		philo.id = i + 1;
		simulation->pid[i] = fork();
		if (simulation->pid[i] == 0)
			philo_pid(&philo);
	}
}

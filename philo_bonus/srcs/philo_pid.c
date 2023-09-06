/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 02:52:46 by romachad          #+#    #+#             */
/*   Updated: 2023/09/06 05:41:00 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	is_dead(void)
{
	sem_t	*dead;

	dead = sem_open("/dead", 0);
	if (dead == SEM_FAILED)
	{
		if (errno == ENOENT)
		{
			printf("non existe...\n");
			return (0);
		}
		else
		{
			printf("Abrimos o que? Caixa de pandora...\n");
			return (0);
		}
	}
	else
	{
		printf("I am dead Jim\n");
		return (1);
	}
}

static void	philo_loop(t_philo *philo)
{
	//if (is_dead() == 0)
	//	return ;
	//printf("OI LOOOP. t: %ld, id: %i\n", philo->sim->t_start, philo->id);
	sem_wait(philo->sim->forks);
	sem_wait(philo->sim->print);
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	sem_wait(philo->sim->forks);
	sem_wait(philo->sim->print);
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);

	//printf("peguei garfos?\n");

	//EAT
	sem_wait(philo->control_death);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is eating\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	philo->count_eat++;
	philo->t_last_eat = get_time();
	sem_post(philo->control_death);
	usleep(philo->sim->t_eat);

	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);

	//check if max eat...
	//TBI
	

	//Sleep;
	sem_wait(philo->sim->print);
	printf("%ld\t %i is sleeping\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	usleep(philo->sim->t_sleep);
	

	sem_wait(philo->sim->print);
	printf("%ld\t %i is thinking\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);


}

static void	*death_thread(void *philo_index)
{
	uint64_t	last_eat;
	t_philo		*philo;

	philo = (t_philo *)philo_index;

	//printf("D_thread no comeco, id: %i\n", philo->id);
	sem_wait(philo->control_death);
	//printf("D_thread , id: %i\n", philo->id);
	last_eat = philo->t_last_eat;
	//	printf("D_thread --id: %i\n", philo->id);
	sem_post(philo->control_death);
	//printf("D_thread no meio\n");

	usleep(get_time() - last_eat + philo->sim->t_die);

	//printf("D_thread na espera\n");
	sem_wait(philo->control_death);
	//printf("D_thread pos espera\n");
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
	{
		sem_open("/dead", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
		sem_post(philo->control_death);
		sem_close(philo->control_death);
		return (NULL);
	}
	sem_post(philo->control_death);
	return (NULL);
}

int	philo_pid(t_table *table, int i)
{
	char	*str;

	str = ft_itoa(i);
	table->philos[i].philo_n = ft_strjoin("/philo_", str);
	free(str);
	table->philos[i].control_death = sem_open(table->philos[i].philo_n, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	while (is_dead() == 0)
	{
		//printf("vou criar d_thread\n");
		pthread_create(&table->philos[i].death_thread, NULL, &death_thread, &table->philos[i]);
		//printf("vou entrar no loop\n");
		philo_loop(&table->philos[i]);
		pthread_detach(table->philos[i].death_thread); // Mudar para espera? Melhor criar outro sem p/ controlar o fim do thread....
		if (table->simulation.max_eat == table->philos[i].count_eat)
			break;
	}
	free(table->simulation.pid);
	sem_close(table->simulation.forks);
	sem_close(table->philos[i].control_death);
	sem_unlink(table->philos[i].philo_n);
	free(table->philos[i].philo_n);
	free(table->philos);
	exit (0);
}

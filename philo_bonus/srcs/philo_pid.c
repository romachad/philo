/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 02:52:46 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 05:14:11 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

/*static int	is_dead(void)
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
}*/

static void	end(t_philo *philo)
{
	/*int	i;

	
	sem_wait(philo->control_thread);
	i = philo->thread_counter;
	sem_post(philo->control_thread);
	while (i > 0)
	{
		usleep(1000);
		sem_wait(philo->control_thread);
		i = philo->thread_counter;
		sem_post(philo->control_thread);
	}

	//sem_wait(philo->control_death);
	sem_close(philo->control_death);
	sem_close(philo->sim->forks);
	sem_close(philo->sim->print);
	sem_close(philo->sim->can_eat);
	free(philo->philo_n);
	//free(table->philos);
	free(philo);*/

	sem_wait(philo->sim->print);
	printf("%ld\t %i died\n", (get_time() - philo->sim->t_start)/ 1000, philo->id);
	//sem_close(philo->control_death);
	sem_close(philo->sim->forks);
	sem_close(philo->sim->print);
	sem_close(philo->sim->can_eat);
	//free(philo->philo_n);

	//free(philo);






	exit(1);
}

static int	take_fork(t_philo *philo)
{
	//if (is_dead(philo) == 1)
	//	return (1);
	sem_wait(philo->sim->forks);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo);
	//sem_wait(philo->control_death);
	/*if (philo->is_dead == 1)
		end(philo);*/
	sem_wait(philo->sim->print);
	/*if (is_dead(philo) == 1)
	{
		sem_post(philo->sim->forks);
		sem_post(philo->control_death);
		sem_post(philo->sim->print);
		return (1);
	}*/
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	//sem_post(philo->control_death);
	sem_post(philo->sim->print);
	//sem_post(philo->control_death);
	/*if (is_dead(philo) == 1)
	{
		sem_post(philo->sim->forks);
		return (1);
	}*/
	return (0);
}

static void	philo_loop(t_philo *philo)
{
	//sem_wait(philo->control_death);
	//sem_post(philo->control_death);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo);
	sem_wait(philo->sim->can_eat);
	//sem_wait(philo->control_death);
	//sem_post(philo->control_death);
	
	take_fork(philo);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo);
	take_fork(philo);

	//EAT
	//sem_wait(philo->control_death);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is eating\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	philo->count_eat++;
	philo->t_last_eat = get_time();
	//sem_post(philo->control_death);
	usleep(philo->sim->t_eat);

	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->can_eat);

	//check if max eat...
	//TBI
	

	//Sleep;
	//sem_wait(philo->control_death);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is sleeping\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	//sem_post(philo->control_death);
	usleep(philo->sim->t_sleep);

	

	//sem_wait(philo->control_death);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is thinking\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	//sem_post(philo->control_death);


}

/*static void	*death_thread(void *philo_index)
{
	uint64_t	last_eat;
	t_philo		*philo;

	philo = (t_philo *)philo_index;
	sem_wait(philo->control_death);
	last_eat = philo->t_last_eat;
	sem_post(philo->control_death);
	usleep(get_time() - last_eat + philo->sim->t_die);
	sem_wait(philo->control_death);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
	{
		sem_wait(philo->sim->print);
		printf("%ld\t %i died\n", (get_time() - philo->sim->t_start)/ 1000, philo->id);
		sem_close(philo->control_death);
		sem_close(philo->sim->forks);
		sem_close(philo->sim->print);
		sem_close(philo->sim->can_eat);
		free(philo->philo_n);
		free(philo);
		exit(1);
	}
	sem_post(philo->control_death);
	return (NULL);
}*/

//int	philo_pid(t_table *table, int i)
int	philo_pid(t_philo *philo)
{
	char	*str;

	free(philo->sim->pid);
	while (1)
	{
		philo_loop(philo);
		if (philo->sim->max_eat == philo->count_eat)
			break;
	}
	//free(table->philos);
	end(philo);
	exit (0);
}

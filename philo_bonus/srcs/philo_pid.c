/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 02:52:46 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 06:31:34 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	end(t_philo *philo, int i)
{
	if (i == 1)
	{
		sem_wait(philo->sim->print);
		printf("%ld\t %i died\n", \
				(get_time() - philo->sim->t_start) / 1000, philo->id);
	}
	sem_close(philo->sim->forks);
	sem_close(philo->sim->print);
	sem_close(philo->sim->can_eat);
	exit(i);
}

static void	take_fork(t_philo *philo)
{
	sem_wait(philo->sim->forks);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo, 1);
	sem_wait(philo->sim->print);
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->sim->print);
	printf("%ld\t %i is eating\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	philo->count_eat++;
	philo->t_last_eat = get_time();
	usleep(philo->sim->t_eat);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->can_eat);
}

static void	philo_loop(t_philo *philo)
{
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo, 1);
	sem_wait(philo->sim->can_eat);
	take_fork(philo);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo, 1);
	take_fork(philo);
	eat(philo);
	if (philo->sim->max_eat == philo->count_eat)
		return ;
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo, 1);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is sleeping\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
	usleep(philo->sim->t_sleep);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
		end(philo, 1);
	sem_wait(philo->sim->print);
	printf("%ld\t %i is thinking\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	sem_post(philo->sim->print);
}

int	philo_pid(t_philo *philo)
{
	free(philo->sim->pid);
	if (philo->sim->n_philos == 1)
	{
		printf("%ld\t %i has taken a fork\n", \
				(get_time() - philo->sim->t_start) / 1000, philo->id);
		usleep(philo->sim->t_die);
		end(philo, 1);
	}
	while (1)
	{
		philo_loop(philo);
		if (philo->sim->max_eat == philo->count_eat)
			break ;
	}
	end(philo, 0);
	exit (0);
}

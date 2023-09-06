/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:38:07 by romachad          #+#    #+#             */
/*   Updated: 2023/09/03 02:27:23 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->control_eat);
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is eating\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	philo->count_eat++;
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&philo->sim->control_eat);
	usleep(philo->sim->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->n_fork);
}

static int	first_check(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(philo->n_fork);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->n_fork);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(&philo->fork);
			return (1);
		}
	}
	return (0);
}

int	parity(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(&philo->fork);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->n_fork);
			pthread_mutex_unlock(&philo->fork);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(philo->n_fork);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(philo->n_fork);
			return (1);
		}
	}
	return (0);
}

int	going_to_eat(t_philo *philo)
{
	if (first_check(philo) == 1)
		return (1);
	take_fork(philo);
	if (parity(philo) == 1)
		return (1);
	take_fork(philo);
	eat(philo);
	return (0);
}

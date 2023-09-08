/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 05:07:54 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 06:53:09 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*thread_cicle(void *philo_index)
{
	t_philo	*philo;

	philo = (t_philo *)philo_index;
	while (is_dead(philo) == 0)
	{
		pthread_create(&philo->death_thread, NULL, &death_thread, philo_index);
		philo_loop(philo);
		pthread_detach(philo->death_thread);
		if (philo->count_eat == philo->sim->max_eat)
			return (NULL);
	}
	return (NULL);
}

static void	death_sleep(t_philo *philo)
{
	uint64_t	last_eat;

	pthread_mutex_lock(&philo->sim->end);
	philo->sim->d_thread++;
	pthread_mutex_unlock(&philo->sim->end);
	pthread_mutex_lock(&philo->sim->control_eat);
	last_eat = philo->t_last_eat;
	pthread_mutex_unlock(&philo->sim->control_eat);
	usleep(get_time() - last_eat + philo->sim->t_die);
}

static void	death(t_philo *philo)
{
	philo->sim->is_dead = 1;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i died\n", \
		(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	pthread_mutex_unlock(&philo->sim->control_death);
	pthread_mutex_unlock(&philo->sim->control_eat);
	pthread_mutex_lock(&philo->sim->end);
	philo->sim->d_thread--;
	pthread_mutex_unlock(&philo->sim->end);
}

static void	*death_or_max_eat(t_philo *philo)
{
	if (philo->count_eat == philo->sim->max_eat)
	{
		pthread_mutex_unlock(&philo->sim->control_eat);
		pthread_mutex_lock(&philo->sim->end);
		philo->sim->d_thread--;
		pthread_mutex_unlock(&philo->sim->end);
		return (NULL);
	}
	pthread_mutex_lock(&philo->sim->control_death);
	if (philo->sim->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->sim->control_death);
		pthread_mutex_unlock(&philo->sim->control_eat);
		pthread_mutex_lock(&philo->sim->end);
		philo->sim->d_thread--;
		pthread_mutex_unlock(&philo->sim->end);
		return (NULL);
	}
	death(philo);
	return (NULL);
}

void	*death_thread(void *philo_index)
{
	t_philo		*philo;

	philo = (t_philo *)philo_index;
	death_sleep(philo);
	pthread_mutex_lock(&philo->sim->control_eat);
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
	{
		return (death_or_max_eat(philo));
	}
	pthread_mutex_unlock(&philo->sim->control_eat);
	pthread_mutex_lock(&philo->sim->end);
	philo->sim->d_thread--;
	pthread_mutex_unlock(&philo->sim->end);
	return (NULL);
}

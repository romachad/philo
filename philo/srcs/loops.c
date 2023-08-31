/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:39:59 by romachad          #+#    #+#             */
/*   Updated: 2023/08/31 03:42:35 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->control_death);
	if (philo->sim->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->sim->control_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->control_death);
	return (0);
}

void	philo_loop(t_philo *philo)
{
	if (is_dead(philo) == 1)
		return ;

	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->n_fork);
	
	pthread_mutex_lock(&philo->sim->control_eat);
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\tPhilo %i is about to eat.\n",(get_time() - philo->sim->t_start)/1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&philo->sim->control_eat);
	
	usleep(philo->sim->t_eat);
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\tPhilo %i has eaten.\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->n_fork);
	
	
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\tPhilo %i is about to sleep.\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	usleep(philo->sim->t_sleep);
	
	
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\tPhilo %i is thinking.\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	pthread_mutex_unlock(&philo->sim->print);

}

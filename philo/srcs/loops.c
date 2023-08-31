/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:39:59 by romachad          #+#    #+#             */
/*   Updated: 2023/08/31 05:10:16 by romachad         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i has taken a fork\n",(get_time() - philo->sim->t_start)/1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	pthread_mutex_lock(philo->n_fork);
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i has taken a fork\n",(get_time() - philo->sim->t_start)/1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	
	pthread_mutex_lock(&philo->sim->control_eat);
	//pthread_mutex_lock(&philo->sim->print); --> OLD MESSAGES
	//printf("%ld\tPhilo %i is about to eat.\n",(get_time() - philo->sim->t_start)/1000, philo->id);
	//pthread_mutex_unlock(&philo->sim->print);
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is eating\n",(get_time() - philo->sim->t_start)/1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	
	philo->count_eat++;
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&philo->sim->control_eat);
	
	usleep(philo->sim->t_eat);
	if (is_dead(philo) == 1)
		return ;
	//pthread_mutex_lock(&philo->sim->print); --> OLD MESSAGES
	//printf("%ld\tPhilo %i has eaten.\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	//pthread_mutex_unlock(&philo->sim->print);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->n_fork);
	
	if (philo->count_eat == philo->sim->max_eat)
		return ;
	
	
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is sleeping\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	usleep(philo->sim->t_sleep);
	
	
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is thinking\n", (get_time() - philo->sim->t_start)/1000,philo->id);
	pthread_mutex_unlock(&philo->sim->print);

}

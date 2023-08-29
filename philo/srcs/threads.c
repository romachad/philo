/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 05:07:54 by romachad          #+#    #+#             */
/*   Updated: 2023/08/29 06:17:05 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*thread_cicle(void *philo_index)
{
	t_philo	*philo;

	philo = (t_philo *)philo_index;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->n_fork);
	printf("Philo %i is about to eat. CT: %ld\n",philo->id, get_time() - philo->sim->t_start);
	usleep(philo->sim->t_eat);
	printf("Philo %i has eat. Time passed: %ld\n",philo->id, get_time() - philo->sim->t_start);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->n_fork);
	return (NULL);
}

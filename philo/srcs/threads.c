/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 05:07:54 by romachad          #+#    #+#             */
/*   Updated: 2023/08/31 05:10:57 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"


void	*thread_cicle(void *philo_index)
{
	t_philo	*philo;

	philo = (t_philo *)philo_index;
	if (!(philo->id % 2))
		usleep(500);
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

void	*death_thread(void *philo_index)
{
	t_philo	*philo;
	//uint64_t	time;

	philo = (t_philo *)philo_index;
	//printf("Death philo %i will sleep for about: %ld\n",philo->id, get_time() - philo->t_last_eat + philo->sim->t_die);

	usleep(get_time() - philo->t_last_eat + philo->sim->t_die );
	
	pthread_mutex_lock(&philo->sim->control_eat);
	//printf("Philo %d TL: %ld\n", philo->id, get_time() - philo->t_last_eat);
	//if (get_time() >= (philo->sim->t_die + philo->t_last_eat) || ((get_time() - philo->t_last_eat)/1000) == 0)
	if (get_time() >= (philo->sim->t_die + philo->t_last_eat))
	{
		pthread_mutex_lock(&philo->sim->control_death);
		if (philo->sim->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->sim->control_death);
			pthread_mutex_unlock(&philo->sim->control_eat);
			return (NULL);
		}
		philo->sim->is_dead = 1;
		//printf("Philo %i has died."\
	//		       " CT: %ld. Diff: %ld\n",philo->id, get_time() - philo->sim->t_start, time - philo->t_last_eat);
		//pthread_mutex_lock(&philo->sim->print);
		//printf("%ld\tPhilo %i has died.\n",(get_time() - philo->sim->t_start)/1000,philo->id);
		//pthread_mutex_unlock(&philo->sim->print);
		pthread_mutex_lock(&philo->sim->print);
		printf("%ld\t %i died\n",(get_time() - philo->sim->t_start)/1000,philo->id);
		pthread_mutex_unlock(&philo->sim->print);
		pthread_mutex_unlock(&philo->sim->control_death);
	}
	pthread_mutex_unlock(&philo->sim->control_eat);
	/*while (philo->is_dead == 0)
	{
		time =  get_time();
		//if ((get_time() - philo->t_last_eat) >= philo->sim->t_die)
		if (time >= (philo->sim->t_die + philo->t_last_eat))
		{
			philo->is_dead = 1;
			printf("Philo %i has died."\
				       " CT: %ld. Diff: %ld\n",philo->id, get_time() - philo->sim->t_start, time - philo->t_last_eat);
		}
	}*/
	return (NULL);
}

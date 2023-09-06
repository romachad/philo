/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:14:17 by romachad          #+#    #+#             */
/*   Updated: 2023/09/03 02:27:54 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	*single_philo_thread(void *philo_index)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_index;
	i = 0;
	while (is_dead(philo) == 0)
	{
		pthread_create(&philo->death_thread, NULL, &death_thread, philo_index);
		pthread_detach(philo->death_thread);
		if (i == 0)
		{
			pthread_mutex_lock(&philo->sim->print);
			printf("%ld\t %i has taken a fork\n", \
					(get_time() - philo->sim->t_start) / 1000, philo->id);
			pthread_mutex_unlock(&philo->sim->print);
		}
		i++;
		usleep(philo->sim->t_die + 1000);
	}
	return (NULL);
}

void	single_philo(t_table *table)
{
	table->philos[0].sim = &table->simulation;
	table->philos[0].t_last_eat = get_time();
	pthread_create(&table->philos[0].p_thread, \
			NULL, &single_philo_thread, &table->philos[0]);
}

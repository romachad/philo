/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:39:59 by romachad          #+#    #+#             */
/*   Updated: 2023/09/02 21:57:51 by romachad         ###   ########.fr       */
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

static void	race_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->c_turn);
	philo->l_turn = philo->sim->global_turn % 3;
	pthread_mutex_unlock(&philo->sim->c_turn);
	while (philo->l_turn != philo->turn)
	{
		usleep(500);
		pthread_mutex_lock(&philo->sim->c_turn);
		philo->l_turn = philo->sim->global_turn % 3;
		pthread_mutex_unlock(&philo->sim->c_turn);
	}
}

static void	go_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is sleeping\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	usleep(philo->sim->t_sleep);
}

void	philo_loop(t_philo *philo)
{
	if (philo->l_race == 1)
		race_condition(philo);
	if (is_dead(philo) == 1)
		return ;
	if (going_to_eat(philo) == 1)
		return ;
	if (philo->l_race == 1)
	{
		pthread_mutex_lock(&philo->sim->c_turn);
		if ((philo->sim->global_turn % 3) == philo->turn)
			philo->sim->global_turn++;
		pthread_mutex_unlock(&philo->sim->c_turn);
	}
	if (philo->count_eat == philo->sim->max_eat)
		return ;
	if (is_dead(philo) == 1)
		return ;
	go_to_sleep(philo);
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is thinking\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
}

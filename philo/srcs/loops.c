/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:39:59 by romachad          #+#    #+#             */
/*   Updated: 2023/09/02 04:25:46 by romachad         ###   ########.fr       */
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

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i has taken a fork\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
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

static void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is eating\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->control_eat);
	print_eat(philo);
	philo->count_eat++;
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&philo->sim->control_eat);
}

static int	going_to_eat(t_philo *philo)
{
	if (first_check(philo) == 1)
		return (1);
	take_fork(philo);
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
	take_fork(philo);
	eat(philo);

	usleep(philo->sim->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->n_fork);
	return (0);
}

void	philo_loop(t_philo *philo)
{
	if (philo->l_race == 1)
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

	if (is_dead(philo) == 1)
	{
		//pthread_mutex_unlock(&philo->sim->control_death);
		return ;
	}
	if (going_to_eat(philo) == 1)
		return ;
	//voltou do loop aumenta 1 no global turn, SE for o seu valor de turn no global...
	if (philo->l_race == 1)
	{
		pthread_mutex_lock(&philo->sim->c_turn);
		//philo->l_turn = philo->sim->global_turn;
		if ((philo->sim->global_turn % 3) == philo->turn)
			philo->sim->global_turn++;
		//printf("TURN: %ld\n", philo->sim->global_turn);
		pthread_mutex_unlock(&philo->sim->c_turn);
	}
	

	if (philo->count_eat == philo->sim->max_eat)
		return ;
	if (is_dead(philo) == 1)
	{
		//pthread_mutex_unlock(&philo->sim->control_death);
		return ;
	}
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is sleeping\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
	usleep(philo->sim->t_sleep);
	if (is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld\t %i is thinking\n", \
			(get_time() - philo->sim->t_start) / 1000, philo->id);
	pthread_mutex_unlock(&philo->sim->print);
}

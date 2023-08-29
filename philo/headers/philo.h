/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:29:57 by romachad          #+#    #+#             */
/*   Updated: 2023/08/29 06:02:09 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_sim
{
	int	n_philos;
	uint64_t	t_die;
	uint64_t	t_eat;
	uint64_t	t_sleep;
	int	max_eat;
	uint64_t	t_start;
}	t_sim;

typedef struct s_philo
{
	int	id;
	int	count_eat;
	uint64_t	t_last_eat;
	pthread_t	p_thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*n_fork;
	t_sim	*sim;
}	t_philo;

typedef struct	s_table
{
	t_philo	*philos;
	t_sim	simulation;
}	t_table;

int	ft_atoi(const char *nptr);
void	init(t_table *table, int argc, char **argv);
void	load(t_table *table);
uint64_t	get_time(void);
void	create_threads(t_table *table);
void	*thread_cicle(void *philo_index);

#endif
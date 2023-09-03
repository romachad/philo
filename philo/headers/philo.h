/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:29:57 by romachad          #+#    #+#             */
/*   Updated: 2023/09/03 01:59:52 by romachad         ###   ########.fr       */
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

typedef struct s_sim
{
	pthread_mutex_t	control_eat;
	pthread_mutex_t	control_death;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	pthread_mutex_t	c_turn;
	int				n_philos;
	int				max_eat;
	int				d_thread;
	int				race;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		t_start;
	uint64_t		global_turn;
	char			is_dead;
}	t_sim;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	*n_fork;
	int				id;
	int				count_eat;
	int				l_race;
	uint64_t		t_last_eat;
	unsigned char	turn;
	unsigned char	l_turn;
	pthread_t		p_thread;
	pthread_t		death_thread;
	t_sim			*sim;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	t_sim	simulation;
}	t_table;

uint64_t	get_time(void);
int			ft_atoi(const char *nptr);
int			is_dead(t_philo *philo);
int			going_to_eat(t_philo *philo);
void		init(t_table *table, int argc, char **argv);
void		load(t_table *table);
void		create_threads(t_table *table);
void		*thread_cicle(void *philo_index);
void		*death_thread(void *philo_index);
void		philo_loop(t_philo *philo);
void		single_philo(t_table *table);

#endif

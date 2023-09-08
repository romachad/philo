/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:29:57 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 03:31:08 by romachad         ###   ########.fr       */
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

# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_sim
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*can_eat;
	int				n_philos;
	int				*pid;
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
	sem_t	*control_death;
	//sem_t	*control_thread;
	char	*philo_n;
	//char	*thread_run;
	int				id;
	int				count_eat;
	int				l_race;
	//int				is_dead;
	//int				thread_counter;
	uint64_t		t_last_eat;
	unsigned char	turn;
	unsigned char	l_turn;
	//pthread_t		p_thread;
	pthread_t		death_thread;
	t_sim			*sim;
//	void			*table;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	t_sim	simulation;
}	t_table;

uint64_t	get_time(void);
int			ft_atoi(const char *nptr);
int			is_dead(t_philo *philo);
//int			is_dead(t_philo *philo);
//int			going_to_eat(t_philo *philo);
void		init(t_table *table, int argc, char **argv);
//void		load(t_table *table);
void		load_philos(t_table *table);
//void		create_threads(t_table *table);
void		create_pids(t_table *table);
//void		*thread_cicle(void *philo_index);
//void		*death_thread(void *philo_index);
//void		philo_loop(t_philo *philo);
//void		single_philo(t_table *table);
int			philo_pid(t_table *table, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:29:57 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 08:24:25 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_sim
{
	uint64_t	t_die;
	uint64_t	t_eat;
	uint64_t	t_sleep;
	uint64_t	t_start;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*can_eat;
	int			n_philos;
	int			*pid;
	int			max_eat;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	uint64_t		t_last_eat;
	t_sim			*sim;
}	t_philo;

uint64_t	get_time(void);
int			ft_atoi(const char *nptr);
void		init(t_sim *simulation, int argc, char **argv);
void		create_pids(t_sim *sim);
void		wait_pid(t_sim *sim);
void		wait_turn(t_philo *philo);
void		clear_sem(t_philo *philo);
int			philo_pid(t_philo *table);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);

#endif

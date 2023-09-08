/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:48:27 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 08:17:17 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	death(t_sim *simulation, int pid_end)
{
	int	i;

	i = -1;
	while (++i < simulation->n_philos)
	{
		if (simulation->pid[i] != pid_end)
			kill(simulation->pid[i], SIGKILL);
	}
}

void	wait_pid(t_sim *simulation)
{
	int	total;
	int	pid_end;
	int	status;
	int	exit_s;

	total = simulation->n_philos;
	while (total > 0)
	{
		pid_end = waitpid(-1, &status, WNOHANG);
		if (pid_end > 0)
		{
			if (WIFEXITED(status))
				exit_s = WEXITSTATUS(status);
			else
				exit_s = -1;
			total--;
			if (exit_s == 1)
			{
				death(simulation, pid_end);
				break ;
			}
		}
	}
}

void	clear_sem(t_philo *philo)
{
	sem_t	*temp;

	if (philo->sim->n_philos % 2 == 1 && philo->id == philo->sim->n_philos)
	{
		sem_unlink("/3");
		temp = sem_open("/1", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
		sem_close(temp);
	}
	else if (philo->id % 2 == 0)
	{
		sem_unlink("/2");
		temp = sem_open("/3", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
		sem_close(temp);
	}
	else
	{
		sem_unlink("/1");
		temp = sem_open("/2", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
		sem_close(temp);
	}
}

static void	waiting(int i)
{
	sem_t	*check;

	while (1)
	{
		if (i == 3)
			check = sem_open("/3", 0);
		else if (i == 2)
			check = sem_open("/2", 0);
		else
			check = sem_open("/1", 0);
		if (check == SEM_FAILED)
		{
			sem_close(check);
			usleep(500);
		}
		else
			break ;
	}
	sem_close(check);
}

void	wait_turn(t_philo *philo)
{
	if (philo->sim->n_philos % 2 == 1 && philo->id == philo->sim->n_philos)
		waiting(3);
	else if (philo->id % 2 == 0)
		waiting(2);
	else
		waiting(1);
}

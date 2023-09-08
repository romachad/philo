/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:48:27 by romachad          #+#    #+#             */
/*   Updated: 2023/09/08 06:32:01 by romachad         ###   ########.fr       */
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

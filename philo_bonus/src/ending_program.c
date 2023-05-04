/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:34:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/04 10:46:11 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_program(t_data *data)
{
	if (data->pid)
		free(data->pid);
	if (data->forks)
		(sem_unlink("/forks"), sem_close(data->forks));
	if (data->printer)
		(sem_unlink("/printer"), sem_close(data->printer));
}

int	error_check(t_data *data, char *fnc, int code)
{
	if (code < 0)
		(printf ("Error: %s\n", fnc), end_program(data));
	return (code);
}

void	kill_the_chld(t_data *data, pid_t *pid)
{
	int	i;

	i = -1;
	while (++i < data->philosophers)
		kill(pid[i], SIGTERM);
}

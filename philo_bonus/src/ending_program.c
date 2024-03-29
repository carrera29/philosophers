/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:34:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 15:45:55 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_program(t_data *data)
{
	if (data->philo)
		(free(data->philo), data->philo = NULL);
	if (data->printer)
		(sem_close(data->printer), sem_unlink("printer"));
	if (data->forks)
		(sem_close(data->forks), sem_unlink("forks"));
}

void	kill_the_child(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->philosophers)
		kill(philo[i].pid, SIGTERM);
}

int	error_check(t_data *data, char *fnc, int code)
{
	if (code < 0)
		(printf ("Error: %s\n", fnc), end_program(data));
	return (code);
}

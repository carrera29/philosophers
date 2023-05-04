/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/04 10:42:40 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_initialization(t_data *data)
{
	(sem_unlink("/forks"), sem_unlink("/printer"));
	data->forks = sem_open("/forks", O_CREAT, O_EXCL, 0644, data->philosophers);
	data->printer = sem_open("/printer", O_CREAT, O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->printer == SEM_FAILED)
		return (printf("Error: sem open\n"), end_program(data), 1);
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (printf("Error: wrong parameters\n"), 1);
	if (argv[5])
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (printf("Error: wrong parameters\n"), 1);
	if (sem_initialization(data) != 0)
		return (1);
	return (0);
}
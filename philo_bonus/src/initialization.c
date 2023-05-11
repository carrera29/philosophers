/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 12:30:02 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_initialization(t_data *data)
{
	(sem_unlink("forks"), sem_unlink("printer"));
	data->forks = sem_open("forks", O_CREAT, 0644, data->philosophers);
	data->printer = sem_open("printer", O_CREAT, 0644, 1);
	if (data->printer == SEM_FAILED || data->forks == SEM_FAILED)
		return (printf("Error: sem open\n"), end_program(data), 1);
	return (0);
}

t_philo	*philo_init(t_data *data, t_philo *philo)
{
	int	i;

	philo = malloc(sizeof(philo) * data->philosophers);
	if (!philo)
		return (printf("Error: malloc\n"), end_program(data), NULL);
	i = -1;
	while (++i < data->philosophers)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].pid = 0;
		philo[i].data = data;
	}
	return (philo);
}

int	set_the_table(t_data *data, char **argv)
{
	data->philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	if (data->philosophers < 1 || data->time_to_die <= 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| (data->must_eat && data->must_eat <= 0))
		return (printf("Error: wrong parameters\n"), 1);
	return (0);
}

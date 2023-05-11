/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:39:39 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 16:04:03 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	enter_the_room(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = ((i + 1) % data->philosophers);
		data->philo[i].meals = 0;
		data->philo[i].stop = 0;
		data->philo[i].data = data;
		if (error_check(data, "mutex init", \
				pthread_mutex_init(&data->mutex[i], NULL)) != 0)
			return (1);
	}
	if (error_check(data, "mutex init", \
			pthread_mutex_init(&data->print_msg, NULL)) != 0)
		return (1);
	return (0);
}

int	malloc_init(t_data *data)
{
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->philosophers);
	data->philo = malloc(sizeof(t_philosopher) * data->philosophers);
	if (!data->mutex || !data->philo)
		return (printf("Error: malloc"), end_program(data), 1);
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	data->philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	if (data->philosophers < 1 || data->time_to_die <= 0 \
		|| (data->time_to_eat < 0 || data->time_to_sleep < 0) \
		|| (data->must_eat && data->must_eat < 0))
		return (printf("Error: wrong parameters\n"), 1);
	if (malloc_init(data) != 0)
		return (1);
	if (enter_the_room(data) != 0)
		return (1);
	return (0);
}

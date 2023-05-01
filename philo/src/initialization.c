/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:39:39 by clcarrer          #+#    #+#             */
/*   Updated: 2023/04/28 11:13:56 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	enter_the_room(t_data *data)
{
	int	i;

	if (!(data->mutex = malloc(sizeof(pthread_mutex_t) * data->philosophers)))
		return (print_error(5), 1);
	if (!(data->philo = malloc(sizeof(t_philosopher) * data->philosophers)))
		return (print_error(5), end_program(data), 1);
	i = 0;
	while (i < data->philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = ((i + 1) % data->philosophers);
		data->philo[i].meals = 0;
		data->philo[i].stop = 0;
		data->philo[i].data = data;
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (print_error(5), end_program(data),  1);
		i++;
	}
	if (pthread_mutex_init(&data->print_msg, NULL) != 0)
			return (print_error(5),end_program(data), 1);
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
			return (print_error(4), 1);
	if (argv[5])
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(4), 1);
	if (enter_the_room(data) != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:53:33 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 16:04:08 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_program(t_data *data)
{
	int	i;

	if (data->philo)
		(free(data->philo), data->philo = NULL);
	if (data->mutex)
	{
		i = -1;
		while (++i < data->philosophers)
			pthread_mutex_destroy(&data->mutex[i]);
		(free(data->mutex), data->mutex = NULL);
	}
	pthread_mutex_destroy(&data->print_msg);
}

int	error_check(t_data *data, char *fnc, int code)
{
	if (code < 0)
		(printf("Error: %s\n", fnc), end_program(data));
	return (code);
}

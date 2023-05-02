/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:38:28 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/02 10:55:38 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_program(t_data *data)
{
	int i;

	i = 0;
	if (data->mutex)
	{
		while (i < data->philosophers)
			pthread_mutex_destroy(&data->mutex[i]);
		(free(data->mutex), data->mutex = NULL);
	}
	if (data->philo)
		(free(data->philo), data->philo = NULL);
	pthread_mutex_destroy(&data->print_msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:34:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/02 12:06:10 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_program(t_data *data)
{
	int		i;

	if (data->sem)
	{
		i = -1;
		while (++i < data->philosophers)
			sem_close(data->sem[i]);
		free(data->sem);
	}
	if (data->print_msg)
		sem_close(data->print_msg);
	if (data->philo)
		(free(data->philo), data->philo = NULL);
}

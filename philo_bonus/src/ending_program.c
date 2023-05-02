/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:34:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/01 20:22:30 by pollo            ###   ########.fr       */
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

void	print_error(int i)
{
	if (i == 0)
		printf("Malloc error\n");
	else if (i == 1)
		printf("Wrong number of arguments\n");
	else if (i == 2)
		printf("Wrong parameters\n");
	else if (i == 3)
		printf("Fork error\n");
	else if (i == 4)
		printf("Wrong parameters\n");
	else if (i == 5)
		printf("Mutex error\n");
	else if (i == 6)
		printf("Fork error\n");
	else if (i == 7)
		printf("Sem error\n");
}

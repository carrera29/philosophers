/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:34:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/26 14:15:02 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_program(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->sem)
		free(data->sem);
}

void	print_error(int i)
{
	if (i == 0)
		printf("Malloc error\n");
	else if (i == 1)
		printf("Wrong number of arguments\n");
	else if (i == 2)
		printf("error with thread creation\n");
	else if (i == 3)
		printf("error with thread join\n");
	else if (i == 4)
		printf("wrong parameters\n");
	else if (i == 5)
		printf("mutex error\n");
	else if (i == 6)
		printf("fork error\n");
	else if (i == 7)
		printf("sem  error\n");
}

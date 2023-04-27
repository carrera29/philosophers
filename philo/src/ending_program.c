/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:38:28 by clcarrer          #+#    #+#             */
/*   Updated: 2023/04/27 11:41:41 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_philosopher *p)
{
	pthread_mutex_destroy(&p->data->mutex[p->left_fork]);
	pthread_mutex_destroy(&p->data->mutex[p->right_fork]);
}

void	end_program(t_data *data)
{
	int i;

	i = 0;
	if (data->mutex != NULL)
	{
		while (i < data->philosophers)
			pthread_mutex_destroy(&data->mutex[i]);
		(free(data->mutex), data->mutex = NULL);
	}
	if (data->philo)
		(free(data->philo), data->philo = NULL);
	pthread_mutex_destroy(&data->print_msg);
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
}

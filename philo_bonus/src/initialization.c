/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/26 15:10:54 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_initialization(t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	while (i < data->philosophers)
	{
		name = ft_itoa(i);
		data->sem[i] = (sem_t)sem_open(name, O_CREAT, O_EXCL, 0660, 1);
		free(name);
		i++;
	}
}

void	enter_the_room(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = ((i + 1) % data->philosophers);
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		i++;
	}
}

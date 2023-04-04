/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/04/04 12:03:47 by clcarrer         ###   ########.fr       */
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
	p->id = i;
	p->left_fork = i;
	p->right_fork = ((i + 1) % data->philosophers);
	p->meals = 0;
	p->data = data;
}

int	sem_initialization(t_data *data)
{
	sem_unlink("fork_two");
	if ((data->fork_one = sem_open("fork_two", O_CREAT, O_EXCL, 0660, 1)) == SEM_FAILED)
		return (print_error(4), 1);
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (print_error(2), 1);
	if (argv[5] != '\0')
	{
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(2), 1);
	}
	data->stop = 0;
	data->philo = NULL;
	if (!(data->philo = malloc(sizeof(data->philo) * data->philosophers)))
        return (print_error(0), 1);
	// if (sem_initialization(data) != 0)
	// 	return (1);
	return (0);
}
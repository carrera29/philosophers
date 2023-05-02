/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/02 09:39:23 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_initialization(t_data *data)
{
	int		i;

	data->sem = malloc(sizeof(sem_t *) * data->philosophers);
	if (!data->sem)
		return (print_error(0), 1);
	i = -1;
	while (i++ < data->philosophers)
	{
		(data->name = ft_itoa(i), sem_unlink(data->name));
		(data->sem[i] = sem_open(data->name, O_CREAT, 0660, 1), free(data->name));
		if (data->sem[i] == SEM_FAILED)
			return (print_error(7), end_program(data), 1);
	}
	data->print_msg = sem_open("sem_print", O_CREAT, 0660, 1);
	if (data->print_msg == SEM_FAILED)
		return (print_error(7), end_program(data), 1);
	return (0);
}

void	enter_the_room(t_data *data, t_philosopher *p, int i)
{
	p->data = data;
	p->id = i;
	p->left_fork = i;
	p->right_fork = ((i + 1) % data->philosophers);
	p->meals = 0;
	p->stop = 0;
}

int	set_the_table(t_data *data, char **argv)
{
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (print_error(2), 1);
	if (argv[5])
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(2), 1);
	if (sem_initialization(data) != 0)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/24 12:58:53 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	lunch_time(t_philosopher *p)
{
	// write_msg("has taken a fork", p->id);
	// if (kitchen_timer(p) != 0)
	// 	return (1);
	gettimeofday(&p->last_meal, NULL);
	(write_msg("is eating", p->id), p->meals++);
	usleep(p->data->time_to_eat * 1000);
	// if (sem_post(data->fork_two) != 0)
	// 	printf("sem_post error\n");
	// write_msg("has left a fork", p->id);
	return (0);
}

void	enter_the_room(t_philosopher *p, t_data *data)
{
	write_msg("enter the room", p->id);
	gettimeofday(&p->last_meal, NULL);
	while (kitchen_timer(p) == 0)
	{	
		sem_wait(data->fork_one);
		write_msg("has taken a fork", p->id);
		if (lunch_time(p) != 0)
			break;
		sem_post(data->fork_one);
		write_msg("has left a fork", p->id);
		write_msg("is sleeping", p->id);
		usleep(p->data->time_to_sleep * 1000);
		write_msg("is thinking", p->id);
	}
}

int	dollys_clone(t_data *data)
{
	int	i;
	int	pid;

	sem_unlink("fork");
	if ((data->fork_one = sem_open("fork", O_CREAT, O_EXCL, 0660, 1)) == SEM_FAILED)
		print_error(4);
    i = 0;
	while (i < data->philosophers)
	{
		if ((pid = fork()) < 0)
			return (end_program(data), print_error(3), 1);
		else if (pid == 0)
		{
			clone_identification(data, &data->philo[i], i);
			enter_the_room(&data->philo[i], data);
			return (0);
		}
		i++;
	}
	wait(NULL);
	end_program(data);
	return (0);
}

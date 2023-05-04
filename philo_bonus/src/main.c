/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:17:37 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/04 12:11:19 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	usleep(500);
	while (1)
	{
		usleep(100);
		if (kitchen_timer(data) == 1)
		{
			data->is_dead = 1;
			write_msg(data, "died", data->id);
			exit (1);
		}
		if (data->must_eat && data->meals >= data->must_eat)
			exit (0);
	}
}

void	time_to_eat(t_data *data)
{
	sem_wait(data->forks);
	write_msg(data, "has taken a fork", data->id);
	sem_wait(data->forks);
	write_msg(data, "has taken a fork", data->id);
	(write_msg(data, "is eating", data->id), data->meals++); 
	gettimeofday(&data->last_meal, NULL);
	usleep(data->time_to_eat * 1000);
	(sem_post(data->forks), sem_post(data->forks));
}

int	time_for_lunch(t_data *data)
{
	pthread_t		thread;

	if (data->id % 2 == 1)
		usleep(500);
	if (pthread_create(&thread, NULL, &monitoring, &data) != 0)
		return (printf("Error: pthread create\n"), 1);
	gettimeofday(&data->last_meal, NULL);
	while (1)
	{
		time_to_eat(data);
		write_msg(data, "is sleeping", data->id);
		usleep(data->time_to_sleep * 1000);
		write_msg(data, "is thinking", data->id);
	}
}

int	enjoy_dinner(t_data *data)
{
	int		i;
	int		status;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * data->philosophers);
	if (!pid)
		return (printf("Error: malloc\n"), end_program(data), 1);
	i = -1;
	while (++i < data->philosophers)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (printf("Error: fork\n"), end_program(data), 1);
		else if (!pid[i])
			(data->id = i, time_for_lunch(data));
	}
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
			kill_the_chld(data, pid);
			break ;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		memset(&data, 0, sizeof(data));
		if (set_the_table(&data, argv) != 0)
			return (1);
		if (enjoy_dinner(&data) != 0)
			return (1);
		end_program(&data);
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

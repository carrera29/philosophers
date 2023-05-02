/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:17:37 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/02 13:21:54 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	time_to_eat(t_philosopher *p, t_data *data)
{
	sem_wait(data->sem[p->left_fork]);
	sem_wait(data->sem[p->right_fork]);
	write_msg(data, "has taken a fork", p->id);
	if (kitchen_timer(p, data) != 0)
		return (1);
	(write_msg(data, "is eating", p->id), p->meals++); 
	gettimeofday(&p->last_meal, NULL);
	usleep(data->time_to_eat * 1000);
	sem_post(data->sem[p->left_fork]);
	sem_post(data->sem[p->right_fork]);
	return (0);
}

void	time_for_lunch(t_philosopher *p, t_data *data)
{
	if (p->id % 2 == 1)
		usleep(500);
	gettimeofday(&p->last_meal, NULL);
	while (!data->is_dead && !p->stop)
	{
		if (data->must_eat)
			if (p->meals >= data->must_eat)
				exit (0);
		if (time_to_eat(p, data) == 1)
			break ;
		write_msg(data, "is sleeping", p->id);
		usleep(data->time_to_sleep * 1000);
		write_msg(data, "is thinking", p->id);
	}
	exit (1);
}

int	enjoy_dinner(t_data *data)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < data->philosophers)
	{
		if (error_check(data, "fork", pid = fork()) < 0)
			return (1);
		else if (pid == 0)
			(enter_the_room(data, &data->philo[i], i), \
				time_for_lunch(&data->philo[i], data));
	}
	while ((pid = waitpid(-1, &data->status, 0)) > 0)
		if (WIFEXITED(data->status) && WEXITSTATUS(data->status) != 0)
			return (end_program(data), 1);
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

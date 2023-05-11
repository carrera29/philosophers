/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:17:37 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 12:55:34 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	time_to_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	write_msg(philo->data, "has taken a fork", philo->id);
	sem_wait(philo->data->forks);
	write_msg(philo->data, "has taken a fork", philo->id);
	if (kitchen_timer(philo->data, philo) != 0)
		return (1);
	(write_msg(philo->data, "is eating", philo->id), philo->meals += 1);
	gettimeofday(&philo->last_meal, NULL);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

void	time_for_lunch(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 1)
		usleep(500);
	gettimeofday(&philo->last_meal, NULL);
	while (1)
	{
		if (philo->data->must_eat)
			if (philo->meals >= philo->data->must_eat)
				break ;
		if (time_to_eat(philo) != 0)
			exit (1);
		write_msg(data, "is sleeping", philo->id);
		usleep(data->time_to_sleep * 1000);
		write_msg(data, "is thinking", philo->id);
	}
	exit (0);
}

int	enjoy_dinner(t_data *data, t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->philosophers)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (printf("Error: malloc\n"), end_program(data), 1);
		else if (philo[i].pid == 0)
			time_for_lunch(data, &philo[i]);
	}
	i = -1;
	while (++i < data->philosophers)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			return (kill_the_child(philo), 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		philo = NULL;
		memset(&data, 0, sizeof(data));
		if (set_the_table(&data, argv) != 0)
			return (1);
		philo = philo_init(&data, philo);
		if (!philo)
			return (1);
		if (sem_initialization(&data) != 0)
			return (1);
		if (enjoy_dinner(&data, philo) != 0)
			return (1);
		end_program(&data);
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

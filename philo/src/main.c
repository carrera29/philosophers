/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:39:52 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/17 09:21:17 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	big_brother(t_data *data)
{
	int				i;
	t_philosopher	*p;

	usleep(500);
	while (1)
	{
		i = -1;
		while (++i < data->philosophers)
		{
			usleep(100);
			p = &(data->philo[i]);
			if (kitchen_timer(p) == 1)
				return (data->is_dead = 1, 0);
			if (p->data->must_eat)
				if (p->meals >= p->data->must_eat)
					p->stop += 1;
		}
	}
	return (0);
}

int	time_to_eat(t_philosopher *p)
{
	pthread_mutex_lock(&p->data->mutex[p->left_fork]);
	write_msg(p->data, "has taken the left fork", p->id);
	pthread_mutex_lock(&p->data->mutex[p->right_fork]);
	write_msg(p->data, "has taken the right fork", p->id);
	if (p->data->is_dead)
		return (1);
	(write_msg(p->data, "is eating", p->id), p->meals++);
	p->last_meal = timer_catch();
	mini_naps(p->data->time_to_eat);
	pthread_mutex_unlock(&p->data->mutex[p->left_fork]);
	pthread_mutex_unlock(&p->data->mutex[p->right_fork]);
	return (0);
}

void	*philosopher(void *philo)
{
	t_philosopher	*p;

	p = (t_philosopher *)philo;
	if (p->id % 2 == 1)
		usleep(500);
	p->last_meal = timer_catch();
	while (!p->data->is_dead && !p->stop)
	{
		if (time_to_eat(p) != 0)
			break ;
		write_msg(p->data, "is sleeping", p->id);
		mini_naps(p->data->time_to_sleep);
		write_msg(p->data, "is thinking", p->id);
	}
	exit (0);
}

void	enjoy_dinner(t_data *data)
{
	int				i;
	t_philosopher	*p;

	p = data->philo;
	data->first_time = timer_catch();
	i = -1;
	while (++i < data->philosophers)
		if (error_check(data, "pthread create", \
			pthread_create(&p[i].thread, NULL, &philosopher, &p[i])) != 0)
			return ;
	big_brother(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		memset(&data, 0, sizeof(data));
		if (set_the_table(&data, argv) != 0)
			return (1);
		enjoy_dinner(&data);
		end_program(&data);
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:39:52 by clcarrer          #+#    #+#             */
/*   Updated: 2023/04/27 18:03:52 by pollo            ###   ########.fr       */
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
			if (kitchen_timer(p) == 1 || data->is_dead)
				return (1);
			if (data->must_eat)
				if (p->meals >= data->must_eat)
					p->stop = 1;
		}
	}
	return (0);
}

void	time_to_eat(t_philosopher *p)
{
	t_data	*d;

	d = p->data;
	pthread_mutex_lock(&d->mutex[p->left_fork]);
	pthread_mutex_lock(&d->mutex[p->right_fork]);
	write_msg(p->data, "has taken a fork", p->id);
	gettimeofday(&p->last_meal, NULL);
	(write_msg(p->data, "is eating", p->id), p->meals++);
	usleep(d->time_to_eat * 1000);
	pthread_mutex_unlock(&d->mutex[p->left_fork]);
	pthread_mutex_unlock(&d->mutex[p->right_fork]);
}

void	*philosopher(void *philo)
{
	t_philosopher	*p;

	p = (t_philosopher *)philo;
	if (p->id % 2 == 1)
		usleep(500);
	gettimeofday(&p->last_meal, NULL);
	write_msg(p->data, "enter the room", p->id);
	while (!p->data->is_dead || !p->stop)
	{
		time_to_eat(p);
		write_msg(p->data, "is sleeping", p->id);
		usleep(p->data->time_to_sleep * 1000);
		write_msg(p->data, "is thinking", p->id);  
	}
	mutex_destroy(p);
	return (0);
}

int	enjoy_dinner(t_data *data)
{
	int				i;
	t_philosopher	*p;

	p = data->philo;
	i = -1;
	while (++i < data->philosophers)
		if (pthread_create(&p[i].thread, NULL, &philosopher, &p[i]) != 0)
			return (print_error(2), end_program(data), 1);
	big_brother(data);
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
			return (2);
	}
	else
		print_error(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:40:02 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/10 10:09:22 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_program(t_data *data)
{
	int	i;

	if (data->philo)
		(free(data->philo), data->philo = NULL);
	if (data->mutex)
	{
		i = -1;
		while (++i < data->philosophers)
			pthread_mutex_destroy(&data->mutex[i]);
		(free(data->mutex), data->mutex = NULL);
	}
	pthread_mutex_destroy(&data->print_msg);
}

int	kitchen_timer(t_philosopher *p)
{
	struct timeval	curr_time;
	int				diff;
	long			curr;
	long			last;

	gettimeofday(&curr_time, NULL);
	curr = ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
	last = ((p->last_meal.tv_sec * 1000) + (p->last_meal.tv_usec / 1000));
	diff = (curr - last) * 1000;
	if (diff >= (p->data->time_to_die * 1000))
		return (write_msg(p->data, "died", p->id), 1);
	return (0);
}

int	write_msg(t_data *data, char *s, int n_philo)
{
	struct timeval	curr_time;

	pthread_mutex_lock(&data->print_msg);
	gettimeofday(&curr_time, NULL);
	printf("%ld Philosopher %d %s\n", (curr_time.tv_sec * 1000) + \
		(curr_time.tv_usec / 1000), (n_philo + 1), s);
	if (s[0] == 'd')
		return (1);
	pthread_mutex_unlock(&data->print_msg);
	return (0);
}

int	error_check(t_data *data, char *fnc, int code)
{
	if (code < 0)
		(printf("Error: %s\n", fnc), end_program(data));
	return (code);
}

int	ft_atoi(const char *str)
{
	long long int	s;
	long long int	r;
	int				i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	s = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			r = (r * 10) + (str[i++] - 48);
		else
			(write(1, "Error: ft_atoi\n", 16), exit (1));
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			(write(1, "Error: ft_atoi\n", 16), exit (1));
	}
	return (s * r);
}

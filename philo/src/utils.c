/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:40:02 by clcarrer          #+#    #+#             */
/*   Updated: 2023/04/27 10:04:00 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("%ld Philosopher %d %s\n", (curr_time.tv_sec * 1000) +\
		(curr_time.tv_usec / 1000), (n_philo+1), s);
	if (ft_strncmp(s, "died", 4) == 0)
		return (data->is_dead = 1, 1);
	pthread_mutex_unlock(&data->print_msg);
	return (0);
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
			return (write(1, "Error\n", 6));
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			return (write(1, "Error\n", 6));
	}
	return (s * r);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < ((unsigned int)n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:36:28 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 15:47:41 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	timer_catch(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

void	write_msg(t_data *data, char *s, int n_philo)
{
	long	curr_time;

	sem_wait(data->printer);
	curr_time = (timer_catch() - data->first_time);
	printf("%ld Philosopher %d %s\n", curr_time, (n_philo + 1), s);
	if (s[0] == 'd')
		return ;
	else
		sem_post(data->printer);
}

int	kitchen_timer(t_data *data, t_philo *philo)
{
	long	curr_time;
	long	diff;

	curr_time = timer_catch();
	diff = (curr_time - philo->last_meal) * 1000;
	if (diff >= (data->time_to_die * 1000))
		return (write_msg(data, "died", philo->id), 1);
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
			return (-1);
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			return (-1);
	}
	return (s * r);
}

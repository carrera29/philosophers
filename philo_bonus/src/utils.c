/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:36:28 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/02 13:14:17 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_msg(t_data *data, char *s, int n_philo)
{
	struct timeval	curr_time;

	sem_wait(data->print_msg);
	gettimeofday(&curr_time, NULL);
	printf("%ld Philosopher %d %s\n", (curr_time.tv_sec * 1000) +\
		(curr_time.tv_usec / 1000), (n_philo + 1), s);
	if (s[0] == 'd')
		return ;
	else
		sem_post(data->print_msg);
}

int	kitchen_timer(t_philosopher *p, t_data *data)
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
		return (write_msg(data, "died", p->id), data->is_dead = 1, 1);
	return (0);
}

int	error_check(t_data *data, char *fnc, int code)
{
	if (code < 0)
		(printf ("Error: %s\n", fnc), end_program(data));
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
			return (-1);
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			return (-1);
	}
	return (s * r);
}

int	ft_contador(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	aux;

	i = ft_contador(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	if (n < 0)
		aux = -n;
	else
		aux = n;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = aux % 10 + 48;
		aux /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

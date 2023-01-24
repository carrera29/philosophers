/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:17:37 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/24 13:01:50 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_for_lunch(t_philosopher *p)
{
	printf("(%d) I'm here for lunch\n", (p->id + 1));
}

int	enjoy_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		data->philo[i].id_fork = fork();
		if (data->philo[i].id_fork == 0)
			time_for_lunch(&data->philo[i]);
		else
			break ;
		i++;
	}
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	t_philosopher	*p;

	p = data->philo;
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (print_error(0), 1);
	if (argv[5] != '\0')
	{
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(4), 1);
	}
	data->is_dead = 0;
	data->philo = NULL;
	data->sem = NULL;
	if (!(data->philo = malloc(sizeof(p) * data->philosophers)))
		return (print_error(0), 1);
	if (!(data->sem = malloc(sizeof(data->sem) * data->philosophers)))
		return (end_program(data), print_error(0), 1);
	enter_the_room(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (set_the_table(&data, argv) != 0)
			return (1);
		if (enjoy_dinner(&data) != 0)
			return (1);
		end_program(&data);
	}
	else
		print_error(1);
	return (0);
}

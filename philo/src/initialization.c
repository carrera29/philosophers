#include "philo.h"

int	mutex_init(t_data *data)
{
	int	i;

	if (!(data->mutex = malloc(sizeof(pthread_mutex_t) * data->philosophers)))
		return (end_program(data), print_error(0), 1);
	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (end_program(data), print_error(5), 1);
		i++;
	}
	return (0);
}

int	enter_the_room(t_data *data)
{
	int	i;
	
	if (!(data->philo = malloc(sizeof(t_philosopher) * data->philosophers)))
		return (print_error(0), 1);
	i = 0;
	while (i < data->philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = ((i + 1) % data->philosophers);
		data->philo[i].meals = 0;
		data->philo[i].stop = 0;
		data->philo[i].data = data;
		if (pthread_mutex_init(&data->philo[i].mutex_checker, NULL) != 0)
			return (end_program(data), print_error(5), 1);
		i++;
	}
	return (0);
}

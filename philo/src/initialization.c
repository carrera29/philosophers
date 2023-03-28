#include "philo.h"

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
		i++;
	}
	data->is_dead = 0;
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	if (!(data->mutex = malloc(sizeof(pthread_mutex_t) * data->philosophers)))
		return (print_error(5), 1);
	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (print_error(5), 1);
		i++;
	}
	if (pthread_mutex_init(data->print_msg, NULL) != 0)
			return (print_error(5), 1);
	return (0);
}

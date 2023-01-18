#include "philo.h"

void	enter_the_room(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = ((i + 1) % data->philosophers);
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		i++;
	}
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (print_error(5), 1);
		i++;
	}
	if ((pthread_mutex_init(&data->sleeping, NULL) != 0)
		|| (pthread_mutex_init(&data->thinking, NULL) != 0))
			return (print_error(5), 1);
	return (0);
}
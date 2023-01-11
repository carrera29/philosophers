#include "philo.h"

void	*philosopher(void * data)
{
	t_data	*p;
	int		num;
	int	c = 0;
	struct timeval	current_time;

	p = (void *)data;
	num = p->n[0];
	printf("Philosopher %d entered the room\n", num);
	while (c < 5)
	{
		pthread_mutex_lock(&mutex);
		(gettimeofday(&current_time, NULL), printf("%d -> Philosopher %d is eating\n", current_time.tv_usec, num));
		usleep(2);
		pthread_mutex_unlock(&mutex);
		(gettimeofday(&current_time, NULL), printf("%d -> Philosopher %d is sleeping\n", current_time.tv_usec, num));
		usleep(2);
		(gettimeofday(&current_time, NULL), printf("%d -> Philosopher %d is thinking\n", current_time.tv_usec, num));
		usleep(2);
		c++;
	}
	return (0);
}

int	enjoy_dinner(t_data *data)
{
	int	i;

	data->philo.id = 0;
	while (data->philo.id < 3)
	{
		if (pthread_create(&data->philo.thread[data->philo.id], NULL, philosopher, (void *)&data) != 0)
			return (print_error(2), end_program(&data->philo), 1);
		data->philo.id++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(data->philo.thread[i], NULL) != 0)
			return (print_error(3), end_program(&data->philo), 1);
		i++;
	}
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	if (ft_atoi(&data->philo, argv[1]) < 2 || ft_atoi(&data->philo, argv[2]) < 0
		|| ft_atoi(&data->philo, argv[3]) < 0|| ft_atoi(&data->philo, argv[4]) < 0)
		return (print_error(4), end_program(&data->philo), 1);
	if (!(data->philo.thread = malloc(sizeof(pthread_t) * ft_atoi(&data->philo, argv[1]))))
		return (print_error(0), 1);
	if (!(data->n = malloc(sizeof(int) * ft_atoi(&data->philo, argv[1]))))
		return (print_error(0), end_program(&data->philo), 1);
	data->time_to_die = ft_atoi(&data->philo, argv[2]);
	data->time_to_eat = ft_atoi(&data->philo, argv[3]);
	data->time_to_sleep = ft_atoi(&data->philo, argv[4]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc == 5)
	{
		if (set_the_table(&data, argv) != 0)
			return (1);
		if (enjoy_dinner(&data) != 0)
			return (1);
	}
	else
		print_error(1);
	return (0);
}

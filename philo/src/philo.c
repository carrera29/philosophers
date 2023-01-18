#include "philo.h"

int	time_to_eat(t_philosopher *p)
{
	t_data	*d;

	d = p->data;
	pthread_mutex_lock(&d->mutex[p->left_fork]);
	write_msg("has taken a fork", p->id);
	pthread_mutex_lock(&d->mutex[p->right_fork]);
	write_msg("has taken a fork", p->id);
	if (is_philo_dead(&d->philo[p->id]) != 0)
		return (1);
	gettimeofday(&p->last_meal, NULL);
	(write_msg("is eating", p->id), p->meals++);
	usleep(d->time_to_eat * 1000);
	pthread_mutex_unlock(&d->mutex[p->left_fork]);
	pthread_mutex_unlock(&d->mutex[p->right_fork]);
	return (0);
}

void	*philosopher(void *philo)
{
	t_philosopher	*p;
	t_data			*d;

	p = (t_philosopher *)philo;
	d = p->data;
	if (p->id % 2 == 1)
		usleep(1000);
	write_msg("enter the room", p->id);
	while (d->is_dead == 0)
	{
		if (time_to_eat(p) != 0)
			break ;
		// pthread_mutex_lock(&d->sleeping);
		write_msg("is sleeping", p->id);
		usleep(d->time_to_sleep * 1000);
		// pthread_mutex_unlock(&d->sleeping);
		// pthread_mutex_lock(&d->thinking);
		write_msg("is thinking", p->id);
		// pthread_mutex_unlock(&d->thinking);
		if (is_philo_dead(&d->philo[p->id]) != 0)
			break ;
	}
	return (0);
}

int	enjoy_dinner(t_data *data)
{
	int				i;
	t_philosopher	*p;

	p = data->philo;
	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_create(&p[i].thread, NULL, &philosopher, &p[i]) != 0)
			return (print_error(2), end_program(data), 1);
		gettimeofday(&p[i].last_meal, NULL);
		i++;
	}
	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_join(p[i].thread, NULL) != 0)
			return (print_error(3), end_program(data), 1);
		i++;
	}
	return (0);
}

int	set_the_table(t_data *data, char **argv)
{
	if ((data->philosophers = ft_atoi(argv[1])) < 2 \
		|| (data->time_to_die = ft_atoi(argv[2])) <= 0 \
		|| (data->time_to_eat = ft_atoi(argv[3])) < 0 \
		|| (data->time_to_sleep = ft_atoi(argv[4])) < 0)
			return (print_error(4), 1);
	if (argv[5] != '\0')
	{
		if ((data->ntimes_must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(4), 1);
	}
	data->is_dead = 0;
	if (!(data->philo = malloc(sizeof(t_philosopher) * data->philosophers)))
		return (print_error(0), 1);
	enter_the_room(data);
	if (!(data->mutex = malloc(sizeof(pthread_mutex_t) * data->philosophers)))
		return (print_error(5), end_program(data), 1);
	if (mutex_init(data) != 0)
		return (end_program(data), 1);
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

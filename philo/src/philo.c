#include "philo.h"

int	check_okay(t_philosopher *p)
{
	pthread_mutex_lock(&p->mutex_checker);
	if (kitchen_timer(p) == 1)
		return (p->data->is_dead = 1, write_msg("died", p->id), 1);
	if (p->data->must_eat > 0)
	{
		if (p->meals >= p->data->must_eat)
			return (p->stop = 1, 1);
	}
	pthread_mutex_unlock(&p->mutex_checker);
	return (0);
}

int	time_to_eat(t_philosopher *p)
{
	t_data	*d;

	d = p->data;
	pthread_mutex_lock(&d->mutex[p->left_fork]);
	write_msg("has taken the left fork", p->id);
	pthread_mutex_lock(&d->mutex[p->right_fork]);
	write_msg("has taken the right fork", p->id);
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

	p = (t_philosopher *)philo;
	if (p->id % 2 == 1)
		usleep(500);
	gettimeofday(&p->last_meal, NULL);
	write_msg("enter the room", p->id);
	while (check_okay(p) == 0 && p->data->is_dead == 0)
	{
		pthread_mutex_lock(&p->mutex_checker);
		if (time_to_eat(p) != 0)
			return (0);
		write_msg("is sleeping", p->id);
		usleep(p->data->time_to_sleep * 1000);
		write_msg("is thinking", p->id);
		pthread_mutex_unlock(&p->mutex_checker);
	}
	mutex_destroy(p);
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
		if ((data->must_eat = ft_atoi(argv[5])) <= 0)
			return (print_error(4), 1);
	}
	data->is_dead = 0;
	data->philo = NULL;
	data->mutex = NULL;
	if (enter_the_room(data) != 0)
		return (1);
	if (mutex_init(data) != 0)
		return (1);
	return (0);
}

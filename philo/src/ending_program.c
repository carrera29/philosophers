#include "philo.h"

void	end_program(t_data *data)
{
	if (data->philo[0].id != '\0')
		(free(data->philo), data->philo = NULL);
	if (data->mutex != NULL)
		(free(data->mutex), data->mutex = NULL);
}

void	p_is_dead(t_data *d, t_philosopher *p)
{
	int		i;

	d->is_dead = 1;
	write_msg("died", p->id);
	i = 0;
	while (i < d->philosophers)
		(d->philo[i].stop = 1, mutex_destroy(&d->philo[i]));
}

void	print_error(int i)
{
	if (i == 0)
		printf("Malloc error\n");
	else if (i == 1)
		printf("Wrong number of arguments\n");
	else if (i == 2)
		printf("error with thread creation\n");
	else if (i == 3)
		printf("error with thread join\n");
	else if (i == 4)
		printf("wrong parameters\n");
	else if (i == 5)
		printf("mutex error\n");
}

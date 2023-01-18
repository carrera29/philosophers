#include "philo.h"

int	is_philo_dead(t_philosopher *p)
{
	struct timeval	curr_time;
	int				result;

	if (p->data->ntimes_must_eat > 0)
	{
		if (p->meals >= p->data->ntimes_must_eat)
			return (p->data->is_dead = 1, 1);
	}
	gettimeofday(&curr_time, NULL);
	result = (((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000)) \
	- ((p->last_meal.tv_sec * 1000) + (p->last_meal.tv_usec / 1000)));
	if (result >= (p->data->time_to_die * 1000))
		return (write_msg("died", p->id), p->data->is_dead = 1, 1);
	return (0);
}

void	end_program(t_data *data)
{
	if (data->philo[0].id != '\0')
		(free(data->philo), data->philo = NULL);
	if (data->mutex != NULL)
		(free(data->mutex), data->mutex = NULL);
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

#include "philo.h"

int	kitchen_timer(t_philosopher *p)
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
		return (write_msg(p->data, "died", p->id), 1);
	return (0);
}

void	mutex_destroy(t_philosopher *p)
{
	pthread_mutex_destroy(&p->data->mutex[p->left_fork]);
	pthread_mutex_destroy(&p->data->mutex[p->right_fork]);
}

int	write_msg(t_data *data, char *s, int n_philo)
{
	struct timeval	curr_time;

	pthread_mutex_lock(data->print_msg);
	gettimeofday(&curr_time, NULL);
	printf("%ld Philosopher %d %s\n", (curr_time.tv_sec * 1000) +\
		(curr_time.tv_usec / 1000), (n_philo+1), s);
	if (ft_strncmp(s, "died", 4) == 0)
		return (data->is_dead = 1, 1);
	pthread_mutex_unlock(data->print_msg);
	return (0);
}

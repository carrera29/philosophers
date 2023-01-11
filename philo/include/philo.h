
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

pthread_mutex_t	mutex;

typedef struct philosopher
{
	pthread_t		*thread;
	int				id;
}					t_philosopher;

typedef struct data
{
	struct timeval	time_now;
	int				*n;
	int				i;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philosopher	philo;
}                   t_data;

void	*philosopher(void * philosopher);

// Utils
int		ft_atoi(t_philosopher *philo, const char *str);

// Control_error
void	end_program(t_philosopher *philo);
void	print_error(int i);

#endif
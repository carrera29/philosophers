
#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals;
	int				stop;
	struct timeval	last_meal;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print_msg;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	t_philosopher	*philo;
}                   t_data;

// initialization
int		enter_the_room(t_data *data);
int		mutex_init(t_data *data);

// utils
int		kitchen_timer(t_philosopher *p);
void	mutex_destroy(t_philosopher *p);
int		write_msg(t_data *data, char *s, int n_philo);

// ending_program
void	end_program(t_data *data);
void	print_error(int i);

#endif
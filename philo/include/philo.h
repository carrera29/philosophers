
#ifndef PHILO_H
# define PHILO_H

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
	struct timeval	last_meal;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	thinking;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				ntimes_must_eat;
	int				is_dead;
	t_philosopher	*philo;
}                   t_data;

// philo
int		time_to_eat(t_philosopher *p);
void	*philosopher(void *philo);
int		enjoy_dinner(t_data *data);
int		set_the_table(t_data *data, char **argv);

// initialization
void	enter_the_room(t_data *data);
int		mutex_init(t_data *data);

// utils
void	write_msg(char *s, int n_philo);
int		ft_atoi(const char *str);

// ending_program
int		is_philo_dead(t_philosopher *p);
void	end_program(t_data *data);
void	print_error(int i);

#endif
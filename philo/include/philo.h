
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
	pthread_t		checker;
	pthread_mutex_t	mutex_checker;
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
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	t_philosopher	*philo;
}                   t_data;

// philo
int		checks_okay(t_philosopher *p);
int		time_to_eat(t_philosopher *p);
void	*philosopher(void *philo);
int		enjoy_dinner(t_data *data);
int		set_the_table(t_data *data, char **argv);

// initialization
void	enter_the_room(t_data *data);
int		mutex_init(t_data *data);

// utils
int		kitchen_timer(t_philosopher *p);
void	mutex_destroy(t_philosopher *p);
void	write_msg(char *s, int n_philo);
int		ft_atoi(const char *str);

// ending_program
void	end_program(t_data *data);
void	p_is_dead(t_data *d, t_philosopher *p);
void	print_error(int i);

#endif
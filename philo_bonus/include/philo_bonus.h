
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <signal.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*printer;
	pid_t			*pid;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	int				status;
	int				id;
	int				meals;
	struct timeval	last_meal;
}					t_data;

// initialization
int		set_the_table(t_data *data, char **argv);
int		enjoy_dinner(t_data *data);

// utils
void	write_msg(t_data *data, char *s, int n_philo);
int		kitchen_timer(t_data *data);
int		ft_atoi(const char *str);

// ending_program
void	end_program(t_data *data);
int		error_check(t_data *data, char *fnc, int code);
void	kill_the_chld(t_data *data, pid_t *pid);

#endif
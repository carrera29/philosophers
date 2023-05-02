
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <signal.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher
{
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
	sem_t			**sem;
	sem_t			*print_msg;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	int				status;
	char			*name;
	t_philosopher	*philo;
}					t_data;

// initialization
void	enter_the_room(t_data *data, t_philosopher *p, int i);
int		set_the_table(t_data *data, char **argv);
int		enjoy_dinner(t_data *data);

// utils
void	write_msg(t_data *data, char *s, int n_philo);
int		kitchen_timer(t_philosopher *p, t_data *data);
int		error_check(t_data *data, char *fnc, int code);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

// ending_program
void	end_program(t_data *data);

#endif
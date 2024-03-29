/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:24:21 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/12 10:34:42 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
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
	long			last_meal;
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
	long			first_time;
	t_philosopher	*philo;
}					t_data;

// end_program
void	end_program(t_data *data);
int		error_check(t_data *data, char *fnc, int code);

// initialization
int		set_the_table(t_data *data, char **argv);

// utils
void	mini_naps(int sleeping_time);
long	timer_catch(void);
int		kitchen_timer(t_philosopher *p);
int		write_msg(t_data *data, char *s, int n_philo);
int		ft_atoi(const char *str);

#endif
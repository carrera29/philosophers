/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:24:21 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/10 10:09:48 by clcarrer         ###   ########.fr       */
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
}					t_data;

// initialization
int		set_the_table(t_data *data, char **argv);

// utils
void	end_program(t_data *data);
int		kitchen_timer(t_philosopher *p);
int		write_msg(t_data *data, char *s, int n_philo);
int		error_check(t_data *data, char *fnc, int code);
int		ft_atoi(const char *str);

#endif
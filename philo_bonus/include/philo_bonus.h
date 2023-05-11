/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:29:20 by clcarrer          #+#    #+#             */
/*   Updated: 2023/05/11 15:47:37 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_philo
{
	int				id;
	int				meals;
	pid_t			pid;
	long			last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*printer;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				status;
	long			first_time;
	t_philo			*philo;
}					t_data;

// initialization
int		sem_initialization(t_data *data);
t_philo	*philo_init(t_data *data, t_philo *philo);
int		set_the_table(t_data *data, char **argv);
int		error_check(t_data *data, char *fnc, int code);

// utils
long	timer_catch(void);
void	write_msg(t_data *data, char *s, int n_philo);
int		kitchen_timer(t_data *data, t_philo *philo);
int		ft_atoi(const char *str);

// ending_program
void	end_program(t_data *data);
void	kill_the_child(t_philo *philo);

#endif
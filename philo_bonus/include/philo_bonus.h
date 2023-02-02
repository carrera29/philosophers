/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:33:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/24 12:41:07 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philosopher
{
	int				pid;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals;
	struct timeval	last_meal;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	sem_t			*fork_one;
	sem_t			*fork_two;
	int				stop;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	t_philosopher	*philo;
}					t_data;

// ending
void	end_program(t_data *data);
void	print_error(int i);

// init
void	clone_identification(t_data *data, t_philosopher *p, int i);
int		sem_initialization(t_data *data);

// lunch_time
int		lunch_time(t_philosopher *p);
void    enter_the_room(t_philosopher *p, t_data *data);
void    identification(t_philosopher *p);
int		dollys_clone(t_data *data);

// philo_bonus
int		set_the_table(t_data *data, char **argv);

// utils
int		kitchen_timer(t_philosopher *p);
void	write_msg(char *s, int n_philo);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif
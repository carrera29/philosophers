/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:33:18 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/26 12:22:21 by clcarrer         ###   ########.fr       */
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

typedef struct s_philosopher
{
	int				id;
	int				id_fork;
	int				left_fork;
	int				right_fork;
	int				meals;
	struct timeval	last_meal;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	sem_t			*sem;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	t_philosopher	*philo;
}					t_data;

// ending
void	end_program(t_data *data);
void	print_error(int i);

//init
void	sem_initialization(t_data *data);
void	enter_the_room(t_data *data);

// philo_bonus
int		set_the_table(t_data *data, char **argv);

// utils
char	*ft_itoa(int n);
void	write_msg(char *s, int n_philo);
int		ft_atoi(const char *str);

#endif
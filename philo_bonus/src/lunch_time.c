/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:31:06 by clcarrer          #+#    #+#             */
/*   Updated: 2023/01/24 12:58:53 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	enter_the_room(t_philosopher *p)
{
    int i;

    i = 0;
    while (i < 3)
    {
        printf("(%d) is eating\n", p->id);
        sleep(3);
        printf("(%d) is sleeping\n", p->id);
        sleep(3);
        printf("(%d) is thinking\n", p->id);
        i++;
    }
}

void	identification(t_philosopher *p)
{
    printf("id is %d\n", p->id);
    printf("L_f is %d\n", p->left_fork);
    printf("R_f is %d\n", p->right_fork);
}

void	clone_identification(t_data *data, t_philosopher *p, int i)
{
	p->id = i;
	p->left_fork = i;
	p->right_fork = ((i + 1) % 4);
	p->meals = 0;
	p->data = data;
}

int	dollys_clone(t_data *data)
{
	int	i;
    int pid;

    if (!(data->philo = malloc(sizeof(data->philo) * data->philosophers)))
        return (print_error(0), 1);
    i = 0;
	while (i < data->philosophers)
	{
		if ((pid = fork()) < 0)
            return (print_error(3), 1);
        else if (pid == 0)
        {
            printf("paso %d\n", i);
			clone_identification(data, &data->philo[i], i);
            identification(&data->philo[i]);
            enter_the_room(&data->philo[i]);
            return (0);
        }
		i++;
	}
	wait(NULL);
	return (0);
}

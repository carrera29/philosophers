#include "philo.h"

void	end_program(t_philosopher *philo)
{
	if (philo->thread != NULL)
		(free(philo->thread), philo->thread = NULL);
	// if (philo->c != NULL)
	// 	(free(philo->c), philo->c = NULL);
}

void	print_error(int i)
{
	if (i == 0)
		printf("Malloc error\n");
	else if (i == 1)
		printf("Wrong number of arguments\n");
	else if (i == 2)
		printf("error with thread creation\n");
	else if (i == 3)
		printf("error with thread join\n");
	else if (i == 4)
		printf("wrong parameters\n");
}

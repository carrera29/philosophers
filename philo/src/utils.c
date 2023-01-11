#include "philo.h"

int	ft_atoi(t_philosopher *philo, const char *str)
{
	long long int	s;
	long long int	r;
	int				i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	s = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			r = (r * 10) + (str[i++] - 48);
		else
			(print_error(4), end_program(philo));
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			(print_error(4), end_program(philo));
	}
	return (s * r);
}

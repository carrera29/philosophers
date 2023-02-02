#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc == 5 || argc == 6)
	{
		if (set_the_table(&data, argv) != 0)
			return (1);
		if (enjoy_dinner(&data) != 0)
			return (1);
		end_program(&data);
	}
	else
		print_error(1);
	return (0);
}

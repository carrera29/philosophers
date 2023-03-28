#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	lunch_time()
{
	write(1, "eating\n", 20);
}

int	main(void)
{
	signal(SIGINT, handler);
	while (1)
	{
		printf("Wasting time %d\n", getpid());
		sleep(1);
	}
	return (0);
}

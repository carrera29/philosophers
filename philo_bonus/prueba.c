#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t		*semaphore;

void	*routine(void *id)
{
	printf("you r in the queue\n");
	sem_wait(semaphore);
	printf("(%d) log in\n", *(int*)id);
	sleep(5);
	printf("(%d) log out\n", *(int*)id);
	sem_post(semaphore);
	return (0);
}

int	main(void)
{
	pthread_t	p[4];
	int			i[4];
	int			x;

	i[0] = 1;
	i[1] = 2;
	i[2] = 3;
	i[3] = 4;
	x = 0;
	sem_unlink("my_semaphore");
	if ((semaphore = sem_open("my_semaphore", O_CREAT, 0660, 1)) == (sem_t *)-1)
		exit(*SEM_FAILED);
	while (x < 4)
		(pthread_create(&p[x], NULL, &routine, &i[x]), x++);
	x = 0;
	while (x < 4)
		(pthread_join(p[x], NULL), x++);
	sem_unlink("my_semaphore");
	sem_close(semaphore);
	return (0);
}

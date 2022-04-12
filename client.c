#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	counter;

	counter = 0;

	if (argc != 3 || !strlen(argv[2]))
	{
		printf("Argument count %d\n", argc);
		return (1);
	}

	printf("sending to pid: %d\n", atoi(argv[2]));
	//mt_kill(ft_atoi(argv[1]), argv[2]);
	while (counter <= 10000)
	{
		kill(atoi(argv[2]), SIGUSR1);
		printf("sending %d\n", atoi(argv[2]));
		counter++;
	}
	printf("Dene!\n");
	return (0);
}

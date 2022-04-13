#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int
modulate(char *message, int receiver_pid)
{
	int		counter;
	int		i;
	char	wave;

	while(message[i]++)
	{	
		wave = message[i];
		counter = 9;
		while(counter--)
		{
			if (wave % 2)
			{
				kill(receiver_pid, SIGUSR2);
			}
			else
			{
				kill(receiver_pid, SIGUSR1);
			}
			wave = wave <<;
		}
	}
}


int
main(int argc, char **argv)
{
	int		counter;
	int 	receiver_pid;

	counter = 0;
	
	if (argc != 3 || !strlen(argv[2]))
	{
		printf("Argument count %d\n", argc);
		return (1);
	}

	receiver_pid = atoi(argv[1]);

	printf("Dene!\n");
	return (0);
}

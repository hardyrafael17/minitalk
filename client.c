#include "minitalk.h"

static status_t	operation;

void
resume(int signo, siginfo_t *info, void *context)
{
		if(!operation.context)
		{
				operation.context = context;
				operation.client_pid = info->si_pid;
				operation.client_pid = signo;
		}
		return;
}

void
send_char(char *string, int message_length)
{
	int		j;
	int		i;

	j = 0;
	while(string && string[j++])
	{
		printf("Sending byte\n");
		i = 8;
		while (i--)
		{
			if (string[j] >> i && 1)
				kill(operation.server_pid, SIGUSR2);
			else
				kill(operation.server_pid, SIGUSR1);
			pause();
		}

	}
	if(string && !message_length)
	{
		//send 0
		printf("Sending end of string\n");
		i = 8;
		while(i--)
		{
				printf("sending bit\n");
				kill(operation.server_pid, SIGUSR1);
				pause();
		}
		return;
	}
	while(message_length--)
	{
		kill(operation.server_pid, SIGUSR1);
		pause();
	}
	//done sending message length
	kill(operation.server_pid, SIGUSR2);
	return;
}

int
main (int argc, char **argv)
{
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction2;

	s_sigaction.sa_sigaction = &resume;
	s_sigaction2.sa_sigaction = &resume;
	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction2.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);

	if (argc != 3 || !strlen(argv[2]))
	{
		printf("Argument count %d\n", argc);
		return (1);
	}
	//check that the server's pid is valid/// TODO
	operation.server_pid = atoi(argv[1]);
	//	
	operation.message = argv[2];
	operation.message_length = strlen(operation.message);
	//sending message length to server
	send_char(NULL, operation.message_length);
	pause();
	//sending messae
	printf("Sending message \n");
	send_char(operation.message, 0);
	printf("Done sending message\n");
	return(0);
}

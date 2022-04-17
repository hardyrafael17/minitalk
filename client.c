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
	j = 0;
	while(string &&string[j++])
	{
		int i;
		i = 8;
		while (i--)
		{
			if (string[j] >> i & 1)
				kill(operation.server_pid, SIGUSR2);
			else
				kill(operation.server_pid, SIGUSR1);
			pause();
		}
		//send 0
		i = 8;
		while(i--)
		{
				kill(operation.server_pid, SIGUSR1);
				pause();
		}
		return;
	}
	printf("sending count\n");
	while(message_length--)
	{
		kill(operation.server_pid, SIGUSR1);
		pause();
	}
	//done sending message length
	printf("Done sending count\n");
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
	//check that the server's pid is valid/// TO DO
	operation.server_pid = atoi(argv[1]);
	//	
	operation.message = argv[2];
	operation.message_length = strlen(operation.message);
	//confirming length
	printf("Message length is %d\n", operation.message_length);
	//sending message length to server
	send_char(NULL, operation.message_length);
	printf("Sent message's length was %d\n", operation.message_length);
	pause();
	//sending messae
	send_char(operation.message, 0);
	return(0);
}

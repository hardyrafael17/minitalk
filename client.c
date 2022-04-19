#include "minitalk.h"
//client

static status_t	operation;

void	send_singal(int type)
{
		int	lock;

		lock = 1;
		if(type && lock)
	   	{
			while (type && lock)
			{
				if(!kill(operation.server_pid, SIGUSR2))
				{
					lock = 0;
				}
			}	
		}
		else
		{
			while (lock)
			{
				if(!kill(operation.server_pid, SIGUSR1))
				{
					lock = 0;
				}
			}	
		}
}

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
	while(string && string[j])
	{
		i = 8;
		while (i--)
		{
			if (string[j] >> i & 1)
			{
				send_singal(1);
			}
			else
			{
				send_singal(0);
			}
			pause();
		}
		++j;
	}
	if(string && !message_length)
	{
		//send 0
		i = 8;
		while(i--)
		{
				send_singal(0);
				pause();
		}
		return;
	}
	// Send message length
	while(message_length--)
	{
		send_singal(0);
		pause();
	}
	send_singal(1);
	pause();
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
	//print server PID
	send_char(NULL, operation.message_length);
	pause();
	//sending messae
	send_char(operation.message, 0);
	printf("Done sending message\n");
	return(0);
}

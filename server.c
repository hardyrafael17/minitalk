#include "minitalk.h"
//server

static data	operation;

void
send_singal(int type)
{
		int	lock;

		lock = 1;
		if(type && lock)
	   	{
			while (type && lock)
			{
				if(!kill(operation.client_pid, SIGUSR2))
				{
					lock = 0;
				}
			}	
		}
		else
		{
			while (lock)
			{
				if(!kill(operation.client_pid, SIGUSR1))
				{
					lock = 0;
				}
			}	
		}
}

void
get_length (int signo, siginfo_t *info, void *context)
{
	//printf("getting length\n");
	operation.message_length++;	
	if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
		send_singal(0);
}

void
alocate_mem (int signo, siginfo_t *info, void *context)
{
		operation.message = calloc(operation.message_length + 1, sizeof(char));
		operation.stage++;
		operation.client_pid = info->si_pid;
		///TODO
		if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
	printf("Done alocating %d Bytes\n", operation.message_length + 1);
	send_singal(0);
}

void
get_message(int signo, siginfo_t *info, void *context)
{
		if(signo == SIGUSR2)
		{ 
		operation.message[operation.counter] += (char) 1 << operation.shift_count;
		}
		operation.shift_count++;
		printf("shift_count >%d<  operation counter >%d<\n", operation.shift_count, operation.counter);
		fflush(stdout);
		if (operation.shift_count == 8)
		{
				if(operation.message[operation.counter] == '\0')
				{
						operation.stage++;
						return;
				}
				operation.shift_count = 0;
				operation.coutner++;
		}
	if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
}

int
main(void)
{
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction2;

	s_sigaction.sa_sigaction = &get_length;
	s_sigaction2.sa_sigaction = &alocate_mem;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction2.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);

	//print server PID
	printf("Server PID %d\n", getpid());
	//flush stdout (performance reasons)
	fflush(stdout);

	while (operation.stage == 0)
	{
		pause();
		send_singal(0);
	}

	s_sigaction.sa_sigaction = &get_message;
	s_sigaction2.sa_sigaction = &get_message;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	
	usleep(400);
	while(operation.stage == 1)
	{
		send_singal(0);
		pause();
	}
	return (0);
}


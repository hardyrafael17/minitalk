#include "minitalk.h"

static data	operation;

void
get_length (int signo, siginfo_t *info, void *context)
{
	operation.message_length++;	
	if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
	kill(operation.client_pid, SIGUSR1);
}

void
alocate_mem (int signo, siginfo_t *info, void *context)
{
		printf("allocating mem, %d\n", operation.message_length);
		operation.message = calloc(operation.message_length + 1, sizeof(char));
		printf("Done!\n");
		operation.stage++;
		operation.client_pid = info->si_pid;
		///TODO
		if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
	kill(info->si_pid, SIGUSR2);
}

void
get_message(int signo, siginfo_t *info, void *context)
{

		if(signo == SIGUSR2)
		{ 
				*(operation.message + operation.counter) = *(operation.message + operation.counter) << 1;		
				operation.shift_count++;
		} else {
				operation.shift_count++;
		}
		if (operation.shift_count == 8)
		{
				if(operation.message[operation.counter] == '\0')
				{
						operation.stage++;
						kill(info->si_pid, SIGUSR2);
						return;
				}
				operation.shift_count = 0;
				operation.coutner++;
		}
		kill(info->si_pid, SIGUSR1);
	if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
	printf("Message ->%s\n", operation.message);
}

int
main(void)
{
	//print server PID
	printf("Server pid %d\n", getpid());
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction2;

	s_sigaction.sa_sigaction = &get_length;
	s_sigaction2.sa_sigaction = &alocate_mem;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction2.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	while(operation.stage == 0)
		pause();
	s_sigaction.sa_sigaction = &get_message;
	s_sigaction2.sa_sigaction = &get_message;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	kill(operation.client_pid, SIGUSR1);
	while(operation.stage == 1)
	{
		pause();
	}
	return (0);
}

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
		printf("allocating mem, %d\n", operation.message_length + 1);
		operation.message = calloc(operation.message_length + 1, sizeof(char));
		printf("Done allocating memory!\n");
		operation.stage++;
		operation.client_pid = info->si_pid;
		///TODO
		if(!operation.client_pid && signo)
	{
		operation.client_pid = (int) info->si_pid;
		//fix later //TODO, error from compilation unused parameter
		operation.context = context;
	}
}

void
get_message(int signo, siginfo_t *info, void *context)
{

		if(signo == SIGUSR2)
		{ 
		//	*(operation.message + operation.counter) = *(operation.message + operation.counter) << 1;		
			printf("bit 1\n");
		} else {
				//operation.shift_count++;
			printf("bit 1\n");
		}
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
	printf("Before getting message, operation stage is = %d\n", operation.stage);

	while(operation.stage == 1)
	{
		kill(operation.client_pid, SIGUSR1);
		pause();
	}
	printf("message ->>%s\n", operation.message);
	return (0);
}

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct info_db_t 
{
	int			coutner;
	int			client_pid;
	char 		*message;
	int			message_length;
	int			counter;
	int			error;
	int			stage;
	int			shift_count;
}					data;

static data	operation;

void
get_length (int signo, siginfo_t *info, void *context)
{
	operation.message_length++;	
	kill(info->si_pid, SIGUSR1);
}

void
alocate_mem (int signo, siginfo_t *info, void *context)
{
		printf("allocating mem, %d\n", operation.message_length);
		operation.message = calloc(operation.message_length + 1, sizeof(char));
		printf("Done!\n");
		operation.stage++;
		kill(info->si_pid, SIGUSR2);
}

void	get_message(int signo, siginfo_t *info, void *context)
{

		if(signo == SIGUSR2)
		{ 
				operation.message[operation.counter] << 1;		
				operation.message[operation.counter]++;		
		} else {
				operation.message[operation.counter]++;
		}
		if (operation.shift_count == 7)
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
}

int
main(void)
{

	//print server PID
	printf("Server PID: %d\n", getpid());
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
	while(operation.stage == 1)
	{
		printf("Pausing on getting message\n");
		pause();
	}
	
	return (0);
}

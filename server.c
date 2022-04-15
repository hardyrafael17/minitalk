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
}					data;

static data	operation;

static
void	action(int signo, siginfo_t *info, void *context)
{
	while(operation.stage == 0)
	{
		if(signo == SIGUSR2)
		{
			operation.message = calloc(operation.message_length + 1, sizeof(char));
			printf("alocating memory-> %d\n", operation.message_length + 1);
			if (!operation.message)
			{
				operation.error = 1;
				return;
			}
			operation.stage++;
			break;
		}
		++operation.message_length;
		pause();
	}
	return;
}

int
main(void)
{

	//print server PID
	printf("Server PID: %d\n", getpid());
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction2;



	s_sigaction.sa_sigaction = &action;
	s_sigaction2.sa_sigaction = &action;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction2.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	while(pause)
	{
		pause();
	}
	return (0);
}

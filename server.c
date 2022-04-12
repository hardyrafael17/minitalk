#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

static void	action(int signo, siginfo_t *info, void *context)
{
	printf("signal received was digit:%d\n", signo);
}

int	main(void)
{
	int	stop;
	pid_t	server_pid;

	server_pid = getpid();
	struct sigaction	s_sigaction;
	stop = 10;

	/*Print server pid */
	printf("Server PID: %d\n", server_pid);

	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (stop)
	{
		pause();
		stop--;
	}
	return (0);
}

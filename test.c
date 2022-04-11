#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int	stop = 1;
void
first_handler(int signo) {
	printf("signal received was :%d", signo);
	if (signo == SIGUSR2)
		stop == 0;
	return;
}

int
main (void)
{
  int	pid;

  pid = getpid();
  printf("Pid is :%d\n", pid);
  while(stop){
  	signal(SIGUSR1, &first_handler);
  	signal(SIGUSR2, &first_handler);
	pause();
  }
}

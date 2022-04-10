#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int	main(void) {
	int		pid;

	pid = getpid();
	printf("pid = %d", pid);
	return (0);
}


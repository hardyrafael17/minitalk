#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct server_status_t
{
	int		send_next;
	int		resend;
	int		pause;
	size_t		message_length;
	int		done;
	int		server_pid;
	char	*message;
	int		stage;
}				status_t;

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

void	send_char(char *string, int message_length);
void	resume(int signo, siginfo_t *info, void *context);
void	get_length (int signo, siginfo_t *info, void *context);
void	alocate_mem (int signo, siginfo_t *info, void *context);
void	get_message(int signo, siginfo_t *info, void *context);

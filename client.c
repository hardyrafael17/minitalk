/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:17:39 by hardy             #+#    #+#             */
/*   Updated: 2022/04/24 17:00:53 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_operation;

int
	send_singal(int type)
{
	int	lock;
	int test;

	lock = 1;
	if(type == 1)
	{
		while (lock)
		{
			if(!kill(g_operation.client_pid, SIGUSR2));
			{
				lock = 0;
			}
		}
	}
	else

	{
		while (lock)
		{
			if(!kill(g_operation.client_pid, SIGUSR1));
			{
				lock = 0;
			}
		}
	}
}

void
	resume(int signo, siginfo_t *info, void *context)
{
   	if (!g_operation.context && signo)
	{
		g_operation.context = context;
		g_operation.client_pid = info->si_pid;
	}
	return ;
}

void
	send_char(char *string, int message_length)
{
	while (string && string[g_operation.counter])
	{
		g_operation.shift_count = 8;
		while (g_operation.shift_count--)
		{
			if (string[g_operation.counter] >> g_operation.shift_count & 1)
				send_singal(1);
			else
				send_singal(0);
			pause();
		}
		++g_operation.counter;
	}
	if (string && !message_length)
	{
		write(1, "he", 2);
		g_operation.shift_count = 8;
		while (g_operation.shift_count-- && send_singal(0))
		{
			write(1, "0", 1);
			pause();
		}
		return ;
	}
	while (g_operation.message_length-- && message_length)
	{
		send_singal(1);
		pause();
	}
	send_singal(0);
	pause();
	return ;
}

int
	main(int argc, char **argv)
{
	static struct sigaction	s_sigaction;
	static struct sigaction	s_sigaction2;

	s_sigaction.sa_sigaction = &resume;
	s_sigaction2.sa_sigaction = &resume;
	
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	if (argc != 3 || !strlen(argv[2]))
	{
		printf("Argument count %d\n", argc);
		return (1);
	}
	g_operation.client_pid = atoi(argv[1]);
	g_operation.message = argv[2];
	g_operation.message_length = strlen(g_operation.message);
	send_char(NULL, 1);
	pause();
	send_char(g_operation.message, 0);
	return (0);
}

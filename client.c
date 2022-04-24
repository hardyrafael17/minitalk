/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:17:39 by hardy             #+#    #+#             */
/*   Updated: 2022/04/20 19:43:25 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_operation;

int
	send_singal(int type)
{
	int	lock;

	lock = 1;
	if (type && lock)
	{
		while (type && lock)
			if (!kill(g_operation.client_pid, SIGUSR2))
				lock = 0;
	}
	else
	{
		while (lock)
		{
			if (!kill(g_operation.client_pid, SIGUSR1))
			{
				lock = 0;
			}	
		}
	}
	printf("sent signal 0 to pid %d then returning\n", g_operation.client_pid);
	fflush(stdout);
	return (1);
}


void
	resume(int signo, siginfo_t *info, void *context)
{
	printf("resuming\n");
	fflush(stdout);
	if (!g_operation.context)
	{
		g_operation.context = context;
		g_operation.client_pid = info->si_pid;
				g_operation.client_pid = signo;
:
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
		g_operation.shift_count = 8;
		while (g_operation.shift_count-- && send_singal(0))
			pause();
		return ;
	}
	while (message_length--)
	{
		printf("-> Sending length with SIGUSR2\n");
		fflush(stdout);
		send_singal(1);
		pause();
	}
	send_singal(0);
	printf("done sending length, sending SIGUSR1\n");
	fflush(stdout);
	pause();
	return ;
}

int
	main(int argc, char **argv)
{
	s_sigaction.sa_sigaction = &resume;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	if (argc != 3 || !strlen(argv[2]))
	{
		printf("Argument count %d\n", argc);
		return (1);
	}
	g_operation.client_pid = atoi(argv[1]);
	g_operation.message = argv[2];
	g_operation.message_length = strlen(g_operation.message);
	send_char(NULL, g_operation.message_length);
	pause();
	send_char(g_operation.message, 0);
	return (0);
}

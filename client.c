/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:17:39 by hardy             #+#    #+#             */
/*   Updated: 2022/04/30 23:33:38 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_operation;

static
	void	send_length(int length)
{
	while (length--)
	{
		send_singal(1, g_operation.client_pid);
		pause();
	}
	send_singal(0, g_operation.client_pid);
	pause();
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
	send_message(char *string)
{
	while (string && string[g_operation.counter])
	{
		g_operation.shift_count = 8;
		while (g_operation.shift_count--)
		{
			if (string[g_operation.counter] >> g_operation.shift_count & 1)
				send_singal(1, g_operation.client_pid);
			else
				send_singal(0, g_operation.client_pid);
			pause();
		}
		++g_operation.counter;
	}
	if (string)
	{
		g_operation.shift_count = 8;
		while (g_operation.shift_count-- && \
		send_singal(0, g_operation.client_pid))
			pause();
		return ;
	}
}

int
	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction2;

	s_sigaction.sa_sigaction = &resume;
	s_sigaction2.sa_sigaction = &resume;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction2, 0);
	if (argc != 3 || !strlen(argv[2]))
	{
		ft_write("Check arguments, Usage: ./client <server_pid> <message>");
		return (1);
	}
	g_operation.client_pid = atoi(argv[1]);
	g_operation.message = argv[2];
	g_operation.message_length = strlen(g_operation.message);
	send_length(g_operation.message_length);
	pause();
	send_message(g_operation.message);
	return (0);
}

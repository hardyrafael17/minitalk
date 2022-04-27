/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:49:00 by hardy             #+#    #+#             */
/*   Updated: 2022/04/24 17:07:31 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>

static t_data	g_operation;

int
	send_singal(int type)
{
	int	lock;
	
	lock = 1;
	while (lock)
		if (!kill(g_operation.client_pid, SIGUSR1))
			lock = 0;
	return (1);
}

void
	calloc_memory(int signo, siginfo_t *info, void *context)
{
	if (!g_operation.client_pid)
	{
		g_operation.client_pid = (int) info->si_pid;
		g_operation.context = context;
	}
	if (signo == SIGUSR2)
	{
		g_operation.message_length++;
	}
	else
	{	
		g_operation.message = calloc(g_operation.message_length + 1, sizeof(char));
		g_operation.stage++;
	}
}

void
	get_message(int signo, siginfo_t *info, void *context)
{
	if (signo == SIGUSR2)
	{
		g_operation.message[g_operation.counter] += \
		(unsigned char) 128 >> g_operation.shift_count;
	}
	g_operation.shift_count++;
	if (g_operation.shift_count == 8)
	{
		if (g_operation.message[g_operation.counter] == '\0')
		{
			g_operation.stage++;
			return ;
		}
		g_operation.shift_count = 0;
		g_operation.counter++;
	}
	if (!g_operation.client_pid && signo)
	{
		g_operation.client_pid = (int) info->si_pid;
		g_operation.context = context;
	}
}

int
	main(void)
{
	printf("Server pid => %d\n", getpid());
	fflush(stdout);
	usleep(500);

	int test;
	static struct sigaction	s_sigaction;
	static struct sigaction	s_sigaction2;

	test = 1;
	while (test--)
	{
		reset(&g_operation);
		s_sigaction.sa_sigaction = &calloc_memory;
		s_sigaction.sa_flags = SA_SIGINFO;
		s_sigaction2.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
		while (g_operation.stage == 0)
		{
			pause();
			send_singal(0);
		}
		s_sigaction.sa_sigaction = &get_message;
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
		usleep(400);
		while (g_operation.stage == 1 && send_singal(0))
			pause();
		printf("%s\n", g_operation.message);
		send_singal(0);
	}
	return (0);
}

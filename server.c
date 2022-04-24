/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:49:00 by hardy             #+#    #+#             */
/*   Updated: 2022/04/20 19:37:22 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_operation;

int
	send_singal(int type)
{
	int	lock;

	printf("operation cleint pid inside signal => %d \n", g_operation.client_pid);
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
			if (!kill(g_operation.client_pid, SIGUSR1))
				lock = 0;
	}
	printf("signo type %d \n", type, g_operation.client_pid);
	fflush(stdout);
	return (1);
}

void
	calloc_memory(int signo, siginfo_t *info, void *context)
{
	printf("Enterign calloc_memory function with signo => %d \n", signo);
	fflush(stdout);
	if (!g_operation.client_pid)
	{
		g_operation.client_pid = (int) info->si_pid;
		printf("assigning client pid=> %d\n", g_operation.client_pid);
		fflush(stdout);
		g_operation.context = context;
	}
	if (signo == SIGUSR2)
	{
		printf("getting length ++\n");
		fflush(stdout);
		g_operation.message_length++;
	}
	else
	{	
		g_operation.message = calloc(g_operation.message_length + 1, sizeof(char));
		g_operation.stage++;
		printf("Alocating memory\n");
		fflush(stdout);
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
	printf("Server PID %d\n", getpid());
	fflush(stdout);
	static struct sigaction	s_sigaction;
	static struct sigaction	s_sigaction2;
	while (1)
	{
		reset(&g_operation);
		s_sigaction.sa_sigaction = &calloc_memory;
		s_sigaction.sa_flags = SA_SIGINFO;
		s_sigaction2.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
		while (g_operation.stage == 0)
		{
			printf("pausing\n");
			fflush(stdout);
			usleep(500);
			pause();
			send_singal(0);
		}
		printf("done with length and memory\n");
		s_sigaction.sa_sigaction = &get_message;
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
		usleep(400);
		while (g_operation.stage == 1 && send_singal(0))
			pause();
		
		printf(">> message >>>%d<<<\n", g_operation.message);
		fflush(stdout);
		send_singal(0);
	}
	return (0);
}


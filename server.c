/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:49:00 by hardy             #+#    #+#             */
/*   Updated: 2022/04/30 23:36:56 by hardy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_operation;

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
		g_operation.message = \
		ft_calloc(g_operation.message_length + 1, sizeof(char));
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

void
	operate(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = &calloc_memory;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (g_operation.stage == 0)
	{
		pause();
		send_singal(0, g_operation.client_pid);
	}
	s_sigaction.sa_sigaction = &get_message;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	usleep(100);
	while (g_operation.stage == 1 && send_singal(0, g_operation.client_pid))
		pause();
	ft_write(g_operation.message);
	free(g_operation.message);
	send_singal(0, g_operation.client_pid);
}

int
	main(void)
{
	printf("Server pid => %d\n", getpid());
	fflush(stdout);
	usleep(100);
	while (1)
	{
		operate();
		g_operation.stage = 0;
		g_operation.client_pid = 0;
		g_operation.message_length = 0;
		g_operation.message = NULL;
		g_operation.counter = 0;
		g_operation.shift_count = 0;
	}
	return (0);
}

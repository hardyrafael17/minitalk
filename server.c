/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:49:00 by hardy             #+#    #+#             */
/*   Updated: 2022/05/21 19:56:48 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_operation;

int
	send_signal(int type, int pid)
{
	int	lock;

	lock = 1;
	usleep(200);
	if (type == 1)
	{
		while (lock)
		{
			if (!kill(pid, SIGUSR2))
			{
				lock = 0;
			}
		}
	}
	else
	{
		while (lock)
		{
			if (!kill(pid, SIGUSR1))
			{
				lock = 0;
			}
		}
	}
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
	if (!g_operation.client_pid && signo && !info)
	{
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
		send_signal(0, g_operation.client_pid);
	}
	s_sigaction.sa_sigaction = &get_message;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	usleep(100);
	while (g_operation.stage == 1 && send_signal(0, g_operation.client_pid))
	{
		pause();
	}
	ft_write(g_operation.message);
	usleep(400);
	free(g_operation.message);
	send_signal(0, g_operation.client_pid);
}

int
	main(void)
{
	int	server_pid;

	server_pid = getpid();
	ft_write("Server PID");
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
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

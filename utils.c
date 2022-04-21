/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:39:39 by hjimenez          #+#    #+#             */
/*   Updated: 2022/02/28 16:59:26 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void
	*ft_calloc(size_t nmemb, size_t size)
{
	char	*pointer;
	size_t	nbytes;
	size_t	i;

	i = 0;
	nbytes = size * nmemb;
	pointer = malloc(nbytes);
	if (!pointer)
		return (NULL);
	while (i < nbytes)
	{
		*(pointer + i) = (char) '\0';
		i++;
	}
	return (pointer);
}

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
			if (!kill(g_operation.client_pid, SIGUSR1))
				lock = 0;
	}
	return (1);
}

void
	reset(void)
{
	g_operation.server_pid = 0;
	g_operation.context = NULL;
	g_operation.client_pid = 0;
	g_operation.message = NULL;
	g_operation.message_length = 0;
	g_operation.counter = 0;
	g_operation.shift_count = 0;
	g_operation.stage = 0;
	return ;
}


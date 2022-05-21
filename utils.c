/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:39:39 by hjimenez          #+#    #+#             */
/*   Updated: 2022/05/21 18:08:49 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int
	send_singal(int type, int pid)
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
	ft_write(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i])
	{
		write(1, &string[i], 1);
		++i;
	}
	write(1, "\n", 1);
	fflush(stdout);
}

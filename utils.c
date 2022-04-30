/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:39:39 by hjimenez          #+#    #+#             */
/*   Updated: 2022/04/30 05:22:37 by hardy            ###   ########.fr       */
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
	send_singal(int type, int pid)
{
	int	lock;

	lock = 1;
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

void	ft_write(char *string)
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
}	

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

void
	reset(t_data *g_operation)
{
	g_operation->context = NULL;
	g_operation->client_pid = 0;
	g_operation->message = NULL;
	g_operation->message_length = 0;
	g_operation->counter = 0;
	g_operation->shift_count = 0;
	g_operation->stage = 0;
	return ;
}


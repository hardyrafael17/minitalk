/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:05:23 by hjimenez          #+#    #+#             */
/*   Updated: 2021/11/12 16:19:36 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*puntero;
	size_t	nbytes;

	nbytes = size * nmemb;
	puntero = malloc(nbytes);
	if (!puntero)
		return (NULL);
	ft_bzero(puntero, nbytes);
	return (puntero);
}

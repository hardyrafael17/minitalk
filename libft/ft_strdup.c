/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:06:44 by hjimenez          #+#    #+#             */
/*   Updated: 2021/11/12 16:24:12 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;

	duplicate = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_memcpy(duplicate, s, ft_strlen(s));
	return (duplicate);
}

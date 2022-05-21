/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:12:10 by hjimenez          #+#    #+#             */
/*   Updated: 2021/10/28 23:07:02 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_string;
	size_t	i;

	if (!s)
		return (NULL);
	new_string = ft_strdup(s);
	if (!new_string)
		return (0);
	i = 0;
	while (*(s + i))
	{
		new_string[i] = (*f)(i, *(s + i));
		i++;
	}
	return (new_string);
}

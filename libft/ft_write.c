/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:57:11 by hjimenez          #+#    #+#             */
/*   Updated: 2022/05/21 18:58:44 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
}

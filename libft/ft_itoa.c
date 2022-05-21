/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:30:17 by hjimenez          #+#    #+#             */
/*   Updated: 2021/11/12 16:21:52 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_convert_number(int n)
{
	size_t	nn;

	if (n < 0)
	{
		nn = (n + 1) * -1;
		nn++;
	}
	else
		nn = n;
	return (nn);
}

static int	get_arr_size(int n)
{
	signed int	sign;
	size_t		stn;
	size_t		arr_length;

	arr_length = 1;
	if (n == 0)
		return (2);
	else if (n == -2147483648)
		return (12);
	if (n < 0)
	{
		sign = -1;
		stn = (n * sign);
		arr_length++;
	}
	else
		stn = n;
	while (stn != 0)
	{
		stn = (stn / 10);
		arr_length++;
	}
	return (arr_length);
}

char	*ft_itoa(int n)
{
	size_t	nn;
	int		arrlength;
	char	*character;
	size_t	index;

	arrlength = get_arr_size(n);
	character = ft_calloc(arrlength--, sizeof(char));
	if (!character)
		return (NULL);
	if (n < 0)
		character[0] = '-';
	nn = ft_convert_number(n);
	if (n == 0)
		character[0] = '0';
	index = 0;
	while (nn != 0)
	{
		*(character + arrlength - 1 - index) = '0' + nn % 10;
		nn = (nn / 10);
		index++;
	}
	return (character);
}

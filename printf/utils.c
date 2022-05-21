/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:24:04 by hjimenez          #+#    #+#             */
/*   Updated: 2021/12/19 19:04:31 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_neg(int o, char *str)
{
	char	*num2;
	int		x;

	x = 0;
	num2 = "-2147483648";
	if (o == -2147483648)
	{
		while (num2[x] != '\0')
		{
			str[x] = num2[x];
			x++;
		}
	}
}

static void	ft_characters(int o, int i, int n, char *str)
{
	int	num;

	num = i;
	if (n < 0)
		n = n * -1;
	while (i >= 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	n = 0;
	str[num + 1] = '\0';
	while (n <= num && o > 0)
	{
		str[n] = str[n + 1];
		n++;
	}
	if (o < 0)
		str[0] = '-';
}

char	*ft_itoa(int num)
{
	int		i;
	char	*str;
	int		n;
	int		o;

	o = num;
	n = num;
	i = 0;
	if (num < 0)
		num = num * -1;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	str = (char *)ft_calloc(i + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (o == -2147483648)
	{
		min_neg(o, str);
		return (str);
	}
	ft_characters(o, i, n, str);
	return (str);
}

char	*ft_itoa_void(unsigned long int n, char *base)
{
	int					size;
	char				*str;
	unsigned long int	num;

	if (n == 0)
		return (NULL);
	size = 0;
	num = n;
	if (num == 0)
		size++;
	while (num != 0)
	{
		num = num / 16;
		size++;
	}
	str = ft_calloc(size + 1, sizeof(char));
	size--;
	while (n >= 16 && 0 < size)
	{
		str[size] = base[n % 16];
		n = n / 16;
		size--;
	}
	str[size--] = base[n % 16];
	return (str);
}

void	ft_printvoid(void *ptr)
{
	char		*strnum;

	strnum = ft_itoa_void((unsigned long int) ptr, "0123456789abcdefg");
	if (!strnum)
		ft_write("0x0", 'n', 'e');
	else
	{	
		ft_write("0x", 'n', 'e');
		ft_write(strnum, 'n', 'i');
	}
}

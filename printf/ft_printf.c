/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:49:52 by hjimenez          #+#    #+#             */
/*   Updated: 2022/03/01 12:59:07 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	va_arg;
	size_t	i;

	i = 0;
	va_start(va_arg, fmt);
	while (*(fmt + i))
	{
		if (*(fmt + i) == '%')
		{
			ft_formatter(va_arg, fmt[i + 1]);
			i += 2;
		}
		else
		{
			ft_write(NULL, fmt[i], 'c');
			i++;
		}
	}
	va_end(va_arg);
	return (ft_write(NULL, 'n', 'd'));
}

int	ft_write(char *str, int c, char task_type)
{
	static int	w_count;
	int			i;

	i = 0;
	if (task_type == 'c' && ++w_count)
		write(1, &c, 1);
	else if (task_type != 'd')
	{
		if (!str)
		{
			write(1, "(null)", 6);
			w_count += 6;
			return (w_count);
		}
		while (*(str + i) && ++w_count)
			write(1, &str[i++], 1);
	}
	if (task_type == 'i')
		free(str);
	if (task_type == 'd')
	{
		i = w_count;
		w_count = 0;
	}
	return (i);
}

void	ft_formatter(va_list args, char c)
{
	if (c == 'c')
		ft_write(NULL, va_arg(args, int), 'c');
	if (c == 's')
		ft_write(va_arg(args, char *), 'n', 'e');
	if (c == 'p')
		ft_printvoid(va_arg(args, void *));
	if (c == 'd' || c == 'i')
		ft_write(ft_itoa(va_arg(args, int)), 'n', 'i');
	if (c == 'u')
		ft_write(ft_ib(va_arg(args, int), "0123456789", 10), 'n', 'i');
	if (c == 'x')
		ft_write(ft_ib(va_arg(args, int), "0123456789abcdef", 16), 'n', 'i');
	if (c == 'X')
		ft_write(ft_ib(va_arg(args, int), "0123456789ABCDEF", 16), 'n', 'i');
	if (c == '%')
		ft_write(NULL, '%', 'c');
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	while (i < count)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_ib(unsigned int n, char *base, unsigned int base_size)
{
	int				size;
	char			*a;
	unsigned int	num;

	size = 0;
	num = n;
	if (num == 0)
		size++;
	while (num != 0)
	{
		num = num / base_size;
		size++;
	}
	a = ft_calloc(size + 1, sizeof(char));
	size--;
	while (n >= base_size && 0 < size)
	{
		a[size] = base[n % base_size];
		n = n / base_size;
		size--;
	}
	a[size--] = base[n % base_size];
	return (a);
}

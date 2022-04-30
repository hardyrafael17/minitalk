/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:33:02 by hjimenez          #+#    #+#             */
/*   Updated: 2021/12/18 21:36:27 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int				ft_write(char *str, int c, char task_type);
int				ft_printf(const char *fmt, ...);
void			*ft_calloc(size_t count, size_t size);
char			*ft_itoa(int num);
void			ft_printvoid(void *ptr);
char			*ft_ib(unsigned int n, char *base, unsigned int base_size);
void			ft_formatter(va_list args, char c);
void			*ft_calloc(size_t count, size_t size);

#endif

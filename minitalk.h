/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:42:55 by hardy             #+#    #+#             */
/*   Updated: 2022/05/21 18:59:39 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct s_operation_db
{
	int		client_pid;
	char	*message;
	int		message_length;
	int		counter;
	int		stage;
	int		shift_count;
	void	*context;
}			t_data;

void	operate(void);
void	ft_write(char *string);
void	resume(int signo, siginfo_t *info, void *context);
void	alocate_mem(int signo, siginfo_t *info, void *context);
void	get_message(int signo, siginfo_t *info, void *context);
void	reset(t_data *g_operation);

#endif

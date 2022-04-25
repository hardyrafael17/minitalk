/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardy <hardy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:42:55 by hardy             #+#    #+#             */
/*   Updated: 2022/04/20 19:36:55 by hardy            ###   ########.fr       */
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

int		send_singal(int type);
void	send_char(char *string, int message_length);
void	resume(int signo, siginfo_t *info, void *context);
void	get_length(int signo, siginfo_t *info, void *context);
void	alocate_mem(int signo, siginfo_t *info, void *context);
void	get_message(int signo, siginfo_t *info, void *context);
void	*ft_calloc(size_t nmemb, size_t size);
void	reset(t_data *g_operation);

#endif

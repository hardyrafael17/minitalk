/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:39:44 by hjimenez          #+#    #+#             */
/*   Updated: 2021/11/16 19:33:41 by hjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **p, t_list *new)
{
	t_list	*lst;

	if (*p)
	{	
		lst = ft_lstlast(*p);
		lst->next = &*new;
	}
	else
		*p = new;
}

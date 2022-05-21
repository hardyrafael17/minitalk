# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjimenez <hjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 17:38:03 by jpineiro          #+#    #+#              #
#    Updated: 2021/11/16 18:57:42 by hjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS_MAND	=	ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_strlen.c			\
				ft_bzero.c			\
				ft_memset.c			\
		  		ft_memcpy.c			\
				ft_memmove.c		\
		  		ft_strlcpy.c		\
		  		ft_strlcat.c		\
				ft_tolower.c		\
		  		ft_toupper.c		\
				ft_strncmp.c		\
				ft_atoi.c			\
				ft_memchr.c			\
				ft_calloc.c			\
				ft_putendl_fd.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_memcmp.c			\
				ft_strdup.c			\
		  		ft_itoa.c			\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_strchr.c			\
		  		ft_strrchr.c		\
		 		ft_strnstr.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_putnbr_fd.c		\


SRCS_BON	=	ft_lstnew_bonus.c			\
				ft_lstadd_front_bonus.c		\
				ft_lstsize_bonus.c			\
				ft_lstlast_bonus.c			\
				ft_lstadd_back_bonus.c		\
				ft_lstdelone_bonus.c		\
				ft_lstclear_bonus.c			\
				ft_lstiter_bonus.c			\
				ft_lstmap_bonus.c			\

OBJS_MAND	= ${SRCS_MAND:.c=.o}

OBJS_BON	= ${SRCS_BON:.c=.o}


CC		= gcc

RM		= rm -rf

AR		= ar rcs

CFLAGS = -Wall -Werror -Wextra

LFLAGS = -I.

all	:	$(NAME)

$(NAME)	:	$(OBJS_MAND)
		$(AR) $(NAME) $(OBJS_MAND)

%.o:	%.c
		$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

bonus	: $(OBJS_BON)
		$(AR) $(NAME) $(OBJS_BON)

clean	:	
		$(RM) ${OBJS_MAND} ${OBJS_BON}

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY:		all clean fclean re bonus

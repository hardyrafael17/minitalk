NAME	=	minitalk.a

SRCS	=	server.c client.c utils.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

RM		= rm -rf

AR		= ar rcs

CFLAGS = -Wall -Werror -Wextra

XFLAGS = -o

all	:		$(NAME)

$(NAME)	:	$(OBJS) 
			@$(AR) $(NAME) $(OBJS)

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:	
			@$(RM) ${OBJS}

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

#personal rules

client: 
			gcc client.c utils.c -o tclient.o

server:
			gcc server.c utils.c -o tserver.o

k: fclean client server

.PHONY:		all clean fclean re bonus

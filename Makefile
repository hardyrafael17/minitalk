NAME	=	minitalk.a

SRCS	=	server2.c client.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

RM		= rm -rf

AR		= ar rcs

CFLAGS = -Wall -Werror -Wextra

XFLAGS = -o

RUN_FLAGS = "Hola mundo Hola mundo ola mundo HHola mundo Hola mundo ola mundo ola mundo Hola mundo ola mundo"

all	:		$(NAME)

$(NAME)	:	$(OBJS) 
			$(AR) $(NAME) $(OBJS)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:	
			$(RM) ${OBJS}

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

#personal rules

excecutable: all
			$(CC) client.o $(XFLAGS) tclient && $(CC) server2.o $(XFLAGS) tserver

vim: excecutable
			echo "compliation completed"

.PHONY:		all clean fclean re bonus

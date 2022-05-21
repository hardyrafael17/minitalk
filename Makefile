# Files...
SERVER		=	server.c

CLIENT		=	client.c

LIBFT		=	cd libft && make

LIB			=	libft/libft.a

NAME	=	minitalk.a

# Sources and objects...
SERVER_SRC	=	$(SERVER)

SERVER_OBJS	=	$(SERVER_SRC:.c=.o)

CLIENT_SRC	=	$(CLIENT)

CLIENT_OBJS	=	$(CLIENT_SRC:.c=.o)

OBJS		=	$(CLIENT_OBJS) \
				$(SERVER_OBJS)

# Literals

GCC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

INCLUDE		=	-I include

SERVER_NAME	=	server

CLIENT_NAME	=	client

NAME		=	server
CC		= gcc

RM		= rm -rf

AR		= ar rcs

CFLAGS = -Wall -Werror -Wextra

XFLAGS = -o

# Rules

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

all: $(NAME)

$(NAME): comp_start ft_server ft_client

comp_start:
	@$(COMP_START)
	@$(LIBFT)

ft_server: $(SERVER_OBJS)
	@$(GCC) $(FLAGS) $(SERVER_OBJS) $(LIB) -o $(SERVER_NAME)
	@$(SERV_READY)

ft_client: $(CLIENT_OBJS)
	@$(GCC) $(FLAGS) $(CLIENT_OBJS) $(LIB) -o $(CLIENT_NAME)
	@$(CLI_READY)

clean:
	@rm -rf $(OBJS)
	@cd libft && make clean
	@$(CLEANED)

fclean: clean
	@rm -rf $(SERVER_NAME) $(CLIENT_NAME)
	@cd libft && make fclean
	@$(FCLEANED)

.c.o:
	@${GCC} ${FLAGS} $(INCLUDE) -c $< -o ${<:.c=.o}

re:	fclean all

.PHONY: all minitalk server client clean fclean re libft
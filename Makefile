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

RM		= rm -rf

AR		= ar rcs

CFLAGS = -Wall -Werror -Wextra

XFLAGS = -o

# Rules

all: $(NAME)

$(NAME): comp_start ft_server ft_client

comp_start:
	@$(COMP_START)
	@$(LIBFT)

ft_server: $(SERVER_OBJS)
	@$(GCC) $(FLAGS) $(LIB) $(SERVER_OBJS)  -o $(SERVER_NAME)

ft_client: $(CLIENT_OBJS)
	@$(GCC) $(FLAGS) $(LIB) $(CLIENT_OBJS)  -o $(CLIENT_NAME)

clean:
	@rm -rf $(OBJS)
	cd libft && make clean

fclean: clean
	@rm -rf $(SERVER_NAME) $(CLIENT_NAME) minitalk.a
	@cd libft && make fclean

.c.o:
	@${GCC} ${FLAGS} $(INCLUDE) -c $< -o ${<:.c=.o}

re:	fclean all

.PHONY: all minitalk server client clean fclean re libft
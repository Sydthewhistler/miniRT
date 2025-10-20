NAME	= miniRT
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I./includes -I./libft -I./minilibx-linux
LIBRARIES = libft/libft.a minilibx-linux/libmlx.a

SRCS	= srcs/main.c \
		  srcs/parsing/parsing_by_type.c \
		  srcs/parsing/parsing_calcul.c \
		  srcs/parsing/parsing_master.c \
		  srcs/process/process_master.c \
		  srcs/utils/error.c \
		  srcs/utils/free.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)

start : download
	@cd libft && make && make clean

download :
	@wget https://cdn.intra.42.fr/document/document/40722/minilibx-linux.tgz
	@tar -xvf minilibx-linux.tgz && rm -rf minilibx-linux.tgz
	@cd minilibx-linux && make

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

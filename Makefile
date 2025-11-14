NAME	= miniRT
NAME_BONUS = miniRT_bonus

CC		= cc
INCLUDE = -I./mandatory/includes -I./libft -I./minilibx-linux
INCLUDE_BONUS = -I./bonus/includes -I./libft -I./minilibx-linux
CFLAGS	= -Wall -Wextra -Werror -g3

LIBRARIES = libft/libft.a minilibx-linux/libmlx.a

SRCS	= mandatory/srcs/main.c \
		  mandatory/srcs/parsing/parsing_by_type.c \
		  mandatory/srcs/parsing/parsing_calcul.c \
		  mandatory/srcs/parsing/parsing_master.c \
		  mandatory/srcs/process/process_master.c \
		  mandatory/srcs/utils/error.c \
		  mandatory/srcs/utils/free.c \
		  mandatory/srcs/utils/utils.c

SRCS_BONUS	= bonus/srcs/main.c \
		  bonus/srcs/parsing/parsing_by_type.c \
		  bonus/srcs/parsing/parsing_calcul.c \
		  bonus/srcs/parsing/parsing_master.c \
		  bonus/srcs/process/process_master.c \
		  bonus/srcs/utils/error.c \
		  bonus/srcs/utils/free.c \
		  bonus/srcs/utils/utils.c

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

mandatory/%.o: mandatory/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus/%.o: bonus/%.c
	$(CC) $(CFLAGS) $(INCLUDE_BONUS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBRARIES) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INCLUDE_BONUS) $(OBJS_BONUS) $(LIBRARIES) -o $(NAME_BONUS)

start : download 
	@cd libft && make && make clean 

download : 
	@wget https://cdn.intra.42.fr/document/document/40722/minilibx-linux.tgz 
	@tar -xvf minilibx-linux.tgz && rm -rf minilibx-linux.tgz 
	@cd minilibx-linux && make

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

superclean: fclean 
	@cd libft && make fclean 
	@rm -rf minilibx-linux

re: fclean all

.PHONY: all bonus clean fclean re

NAME = miniRT

SRCS = mandatory/srcs/parsing/parsing_master.c \
       mandatory/srcs/parsing/parsing_ambient.c \
       mandatory/srcs/parsing/parsing_objects.c \
       mandatory/srcs/parsing/parsing_calcul.c \
       mandatory/srcs/graphics/init.c \
       mandatory/srcs/graphics/hooks.c \
       mandatory/srcs/graphics/ray.c \
       mandatory/srcs/graphics/color.c \
       mandatory/srcs/graphics/hit.c \
       mandatory/srcs/graphics/light.c \
       mandatory/srcs/graphics/objects/sphere.c \
       mandatory/srcs/graphics/objects/planes.c \
       mandatory/srcs/graphics/objects/cylinder.c \
       mandatory/srcs/utils/free.c \
       mandatory/srcs/utils/error.c \
       mandatory/srcs/utils/utils.c \
       mandatory/srcs/utils/op_vector.c \
       mandatory/srcs/utils/op_vec_two.c \
       mandatory/srcs/main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Imandatory/includes -I./libft -I./minilibx-linux
LDFLAGS = -lm -lX11 -lXext

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
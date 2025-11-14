NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iincludes -I./minilibx-linux
LDFLAGS = -lm -lX11 -lXext

MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

SRCS = srcs/main.c \
       srcs/free.c \
       srcs/op_vector.c \
       srcs/op_vec_two.c \
	   srcs/graphics/init.c \
	   srcs/graphics/hooks.c \
	   srcs/graphics/ray.c \
	   srcs/graphics/color.c \
	   srcs/graphics/hit.c \
	   srcs/graphics/light.c \
	   srcs/graphics/objects/sphere.c \
	   srcs/graphics/objects/planes.c \
	   srcs/graphics/objects/cylinder.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "📥 Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git; \
	fi
	@echo "🔨 Building MiniLibX..."
	@make -C $(MLX_PATH) > /dev/null 2>&1
	@echo "✓ MiniLibX ready"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) created!"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

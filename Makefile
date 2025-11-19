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
       mandatory/srcs/graphics/hit_sphere.c \
       mandatory/srcs/graphics/hit_plane.c \
       mandatory/srcs/graphics/hit_cylinder.c \
       mandatory/srcs/graphics/light.c \
       mandatory/srcs/graphics/objects/sphere.c \
       mandatory/srcs/graphics/objects/planes.c \
       mandatory/srcs/graphics/objects/cylinder.c \
       mandatory/srcs/graphics/objects/cylinder2.c \
       mandatory/srcs/utils/free.c \
       mandatory/srcs/utils/error.c \
       mandatory/srcs/utils/utils.c \
       mandatory/srcs/utils/op_vector.c \
       mandatory/srcs/utils/op_vec_two.c \
       mandatory/srcs/main.c

SRCS_BONUS = bonus/srcs/parsing/parsing_master.c \
       bonus/srcs/parsing/parsing_ambient.c \
       bonus/srcs/parsing/parsing_objects.c \
       bonus/srcs/parsing/parsing_calcul.c \
       bonus/srcs/graphics/init.c \
       bonus/srcs/graphics/hooks.c \
       bonus/srcs/graphics/ray.c \
       bonus/srcs/graphics/color.c \
       bonus/srcs/graphics/hit.c \
       bonus/srcs/graphics/hit_sphere.c \
       bonus/srcs/graphics/hit_plane.c \
       bonus/srcs/graphics/hit_cylinder.c \
       bonus/srcs/graphics/light.c \
       bonus/srcs/graphics/objects/sphere.c \
       bonus/srcs/graphics/objects/planes.c \
       bonus/srcs/graphics/objects/cylinder.c \
       bonus/srcs/graphics/objects/cylinder2.c \
       bonus/srcs/utils/free.c \
       bonus/srcs/utils/error.c \
       bonus/srcs/utils/utils.c \
       bonus/srcs/utils/op_vector.c \
       bonus/srcs/utils/op_vec_two.c \
       bonus/srcs/main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Imandatory/includes -I./libft -I./minilibx-linux
LDFLAGS = -lm -lX11 -lXext

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

# Couleurs
GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
RESET = \033[0m
BOLD = \033[1m

.SILENT:

all: $(LIBFT) $(MLX) $(NAME)
	echo "\n$(BOLD)$(GREEN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	echo "$(BOLD)$(GREEN)  ✓ miniRT ready! 🚀$(RESET)"
	echo "$(BOLD)$(GREEN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)\n"

$(LIBFT):
	echo "$(BLUE)⚙  Building libft...$(RESET)"
	make -C libft --no-print-directory
	echo "$(GREEN)✓  libft ready$(RESET)"

$(MLX):
	echo "$(BLUE)⚙  Building minilibx...$(RESET)"
	make -C minilibx-linux --no-print-directory
	echo "$(GREEN)✓  minilibx ready$(RESET)"

$(NAME): $(OBJS)
	echo "\n$(CYAN)🔗 Linking miniRT...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

start:
	wget https://cdn.intra.42.fr/document/document/40722/minilibx-linux.tgz
	tar -xvf minilibx-linux.tgz && rm -rf minilibx-linux.tgz
	cd minilibx-linux && make
	cd libft && make

bonus: $(OBJS_BONUS)
	echo "$(CYAN)🔗 Linking miniRT bonus...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)
	echo "$(GREEN)✓ miniRT bonus ready! ✨$(RESET)"

clean:
	echo "$(CYAN)🧹 Cleaning object files...$(RESET)"
	rm -f $(OBJS)
	make -C libft clean --no-print-directory
	echo "$(GREEN)✓  Clean done$(RESET)"

fclean: clean
	echo "$(CYAN)🗑  Removing binaries...$(RESET)"
	rm -f $(NAME)
	make -C libft fclean --no-print-directory
	echo "$(GREEN)✓  Full clean done$(RESET)"

superclean: fclean
	cd libft && make fclean --no-print-directory
	rm -rf minilibx-linux

re: fclean all

.PHONY: all clean fclean superclean re start
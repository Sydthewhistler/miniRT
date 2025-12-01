NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lm -lX11 -lXext
RM = rm -f

# Directories
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/
MANDATORY_DIR = mandatory/srcs/
BONUS_DIR = bonus/srcs/
INCLUDES = -Imandatory/includes -I$(LIBFT_DIR) -I$(MLX_DIR)
INCLUDES_BONUS = -Ibonus/includes -I$(LIBFT_DIR) -I$(MLX_DIR)

# Source files
SRCS = $(MANDATORY_DIR)parsing/parsing_master.c \
       $(MANDATORY_DIR)parsing/parsing_ambient.c \
       $(MANDATORY_DIR)parsing/parsing_objects.c \
       $(MANDATORY_DIR)parsing/parsing_calcul.c \
       $(MANDATORY_DIR)parsing/verify_ambient.c \
       $(MANDATORY_DIR)parsing/verify_camera.c \
       $(MANDATORY_DIR)parsing/verify_cylinder.c \
       $(MANDATORY_DIR)parsing/verify_light.c \
       $(MANDATORY_DIR)parsing/verify_plane.c \
       $(MANDATORY_DIR)parsing/verify_sphere.c \
       $(MANDATORY_DIR)graphics/init.c \
       $(MANDATORY_DIR)graphics/hooks.c \
       $(MANDATORY_DIR)graphics/ray.c \
       $(MANDATORY_DIR)graphics/color.c \
       $(MANDATORY_DIR)graphics/hit.c \
       $(MANDATORY_DIR)graphics/hit_sphere.c \
       $(MANDATORY_DIR)graphics/hit_plane.c \
       $(MANDATORY_DIR)graphics/hit_cylinder.c \
       $(MANDATORY_DIR)graphics/light.c \
       $(MANDATORY_DIR)graphics/objects/sphere.c \
       $(MANDATORY_DIR)graphics/objects/planes.c \
       $(MANDATORY_DIR)graphics/objects/cylinder.c \
       $(MANDATORY_DIR)graphics/objects/cylinder2.c \
       $(MANDATORY_DIR)utils/free.c \
       $(MANDATORY_DIR)utils/error.c \
       $(MANDATORY_DIR)utils/utils.c \
       $(MANDATORY_DIR)utils/op_vector.c \
       $(MANDATORY_DIR)utils/op_vec_two.c \
       $(MANDATORY_DIR)main.c

SRCS_BONUS = $(BONUS_DIR)parsing/parsing_master.c \
             $(BONUS_DIR)parsing/parsing_ambient.c \
             $(BONUS_DIR)parsing/parsing_objects.c \
             $(BONUS_DIR)parsing/parsing_calcul.c \
             $(BONUS_DIR)parsing/verify_ambient.c \
             $(BONUS_DIR)parsing/verify_camera.c \
             $(BONUS_DIR)parsing/verify_cylinder.c \
             $(BONUS_DIR)parsing/verify_light.c \
             $(BONUS_DIR)parsing/verify_plane.c \
             $(BONUS_DIR)parsing/verify_sphere.c \
             $(BONUS_DIR)graphics/init.c \
             $(BONUS_DIR)graphics/hooks.c \
             $(BONUS_DIR)graphics/ray.c \
             $(BONUS_DIR)graphics/color.c \
             $(BONUS_DIR)graphics/hit.c \
             $(BONUS_DIR)graphics/hit_sphere.c \
             $(BONUS_DIR)graphics/hit_plane.c \
             $(BONUS_DIR)graphics/hit_cylinder.c \
             $(BONUS_DIR)graphics/light.c \
             $(BONUS_DIR)graphics/objects/sphere.c \
             $(BONUS_DIR)graphics/objects/planes.c \
             $(BONUS_DIR)graphics/objects/cylinder.c \
             $(BONUS_DIR)graphics/objects/cylinder2.c \
             $(BONUS_DIR)utils/free.c \
             $(BONUS_DIR)utils/error.c \
             $(BONUS_DIR)utils/utils.c \
             $(BONUS_DIR)utils/op_vector.c \
             $(BONUS_DIR)utils/op_vec_two.c \
             $(BONUS_DIR)main.c

# Object files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Library
LIBFT = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a

# Rules
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

bonus: INCLUDES=$(INCLUDES_BONUS)
bonus: $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re bonus

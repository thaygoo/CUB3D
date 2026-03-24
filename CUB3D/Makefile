NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
INC_DIR		= inc
OBJ_DIR		= obj

MLX_DIR		= $(SRC_DIR)/minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a

LIBFT_DIR	= $(SRC_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parsing/parsing.c \
			  $(SRC_DIR)/parsing/read_file.c \
			  $(SRC_DIR)/parsing/parse_elements.c \
			  $(SRC_DIR)/parsing/parse_map.c \
			  $(SRC_DIR)/parsing/check_map.c \
			  $(SRC_DIR)/parsing/find_player.c \
			  $(SRC_DIR)/utils/utils.c \
			  $(SRC_DIR)/draw.c \
			  $(SRC_DIR)/ray.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/hooks.c \
			  $(SRC_DIR)/player.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES	= -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

MLX_FLAGS	= -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

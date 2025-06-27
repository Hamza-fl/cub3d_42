NAME = cub3d
CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)
LDFLAGS = -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
HEADER = includes/cub3d.h 
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)
MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC = parsing/parsing_utils/alloc_matrix.c \
		parsing/parsing_utils/check_xpm.c \
		parsing/parsing_utils/collect_map_lines.c \
		parsing/parsing_utils/ft_print_error.c \
		parsing/parsing_utils/parse_header.c \
		parsing/parsing_utils/parse_map.c \
		parsing/parsing_utils/set_colors.c \
		parsing/parsing_utils/set_texture_path.c \
		parsing/parsing_utils/split_rgb.c \
		parsing/parsing_utils/validate_map.c \
		parsing/ft_parsing.c \
		raycaster/init_game.c \
		raycaster/game_loop.c \
		raycaster/cleanup_game.c \
		raycaster/input_handling.c \
		raycaster/raycaster.c \
		src/main.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

force_libft:
	@true

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

%.o: %.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re force_libft
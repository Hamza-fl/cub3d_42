NAME = cub3d
CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)
LDFLAGS = -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = mandatory/libft
LIBFT_LIB = mandatory/libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
HEADER = includes/cub3d.h 
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)
MLX_DIR = mandatory/minilibx

SRC = mandatory/parsing/parsing_utils/alloc_matrix.c \
		mandatory/parsing/parsing_utils/check_xpm.c \
		mandatory/parsing/parsing_utils/collect_map_lines.c \
		mandatory/parsing/parsing_utils/ft_print_error.c \
		mandatory/parsing/parsing_utils/parse_header.c \
		mandatory/parsing/parsing_utils/parse_map.c \
		mandatory/parsing/parsing_utils/set_colors.c \
		mandatory/parsing/parsing_utils/set_texture_path.c \
		mandatory/parsing/parsing_utils/split_rgb.c \
		mandatory/parsing/parsing_utils/validate_map.c \
		mandatory/parsing/ft_parsing.c \
		mandatory/raycaster/init_game.c \
		mandatory/raycaster/game_loop.c \
		mandatory/raycaster/cleanup_game.c \
		mandatory/raycaster/input_handling.c \
		mandatory/raycaster/raycaster.c \
		mandatory/raycaster/init_pos.c \
		mandatory/raycaster/dda.c \
		mandatory/raycaster/calc_wall.c \
		mandatory/src/main.c \
		mandatory/raycaster/mini_map.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

force_libft:
	@true

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LIBFT_MLX) $(LDFLAGS) -o $(NAME)

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
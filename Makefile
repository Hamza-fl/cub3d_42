NAME = cub3d
NAME_bonus = cub3d_bonus
CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)
LDFLAGS = -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = mandatory/libft
LIBFT_BONUS_DIR = bonus/libft
LIBFT_LIB = mandatory/libft/libft.a
LIBFT_LIB_bonus = bonus/libft/libft.a
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

SRC_BONUS = bonus/parsing/parsing_utils/alloc_matrix.c \
		bonus/parsing/parsing_utils/check_xpm.c \
		bonus/parsing/parsing_utils/collect_map_lines.c \
		bonus/parsing/parsing_utils/ft_print_error.c \
		bonus/parsing/parsing_utils/parse_header.c \
		bonus/parsing/parsing_utils/parse_map.c \
		bonus/parsing/parsing_utils/set_colors.c \
		bonus/parsing/parsing_utils/set_texture_path.c \
		bonus/parsing/parsing_utils/split_rgb.c \
		bonus/parsing/parsing_utils/validate_map.c \
		bonus/parsing/ft_parsing.c \
		bonus/raycaster/init_game.c \
		bonus/raycaster/game_loop.c \
		bonus/raycaster/cleanup_game.c \
		bonus/raycaster/input_handling.c \
		bonus/raycaster/raycaster.c \
		bonus/raycaster/init_pos.c \
		bonus/raycaster/dda.c \
		bonus/raycaster/calc_wall.c \
		bonus/src/main.c \
		bonus/raycaster/mini_map.c

OBJ = $(SRC:.c=.o)
bonus_OBJ = $(SRC_BONUS:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

$(LIBFT_LIB_bonus): force_libft
	make -C $(LIBFT_BONUS_DIR)

force_libft:
	@true

$(NAME_bonus): $(bonus_OBJ) $(LIBFT_LIB_bonus)
	$(CC) $(bonus_OBJ) $(LIBFT_LIB_bonus) $(LDFLAGS) -o $(NAME_bonus)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

bonus: $(LIBFT_LIB_bonus) $(NAME_bonus)

%.o: %.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(bonus_OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBFT_BONUS_DIR)

fclean: clean 
	rm -rf $(NAME)
	rm -rf $(NAME_bonus)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBFT_BONUS_DIR)

re: fclean all

.PHONY: all clean fclean re force_libft
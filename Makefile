NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)
BONUS_CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(BONUS_LIBFT_DIR)
LDFLAGS = -lmlx -framework OpenGL -framework AppKit

# Mandatory libft
LIBFT_DIR = mandatory/libft
LIBFT_LIB = mandatory/libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h

# Bonus libft
BONUS_LIBFT_DIR = bonus/libft
BONUS_LIBFT_LIB = bonus/libft/libft.a
BONUS_LIBFT_HEADER = $(BONUS_LIBFT_DIR)/libft.h

HEADER = includes/cub3d.h 
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)
BONUS_ALL_HEADERS = $(HEADER) $(BONUS_LIBFT_HEADER)
MLX_DIR = mandatory/minilibx

# Mandatory source files
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
		mandatory/raycaster/init_game_utils.c \
		mandatory/raycaster/game_loop.c \
		mandatory/raycaster/cleanup_game.c \
		mandatory/raycaster/input_handling.c \
		mandatory/raycaster/input_handling_utils.c \
		mandatory/raycaster/raycaster.c \
		mandatory/raycaster/init_pos.c \
		mandatory/raycaster/dda.c \
		mandatory/raycaster/calc_wall.c \
		mandatory/src/main.c \
		mandatory/parsing/parsing_utils/map_utils.c \
		mandatory/parsing/parsing_utils/map_utils1.c

# Bonus source files
BONUS_SRC = bonus/parsing/parsing_utils/alloc_matrix.c \
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
		bonus/raycaster/mini_map.c \
		mandatory/parsing/parsing_utils/map_utils.c \
		mandatory/parsing/parsing_utils/map_utils1.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Default target builds mandatory
all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

# Bonus target
bonus: $(BONUS_LIBFT_LIB) $(MLX_LIB) $(BONUS_NAME)

# Build mandatory libft
$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

# Build bonus libft
$(BONUS_LIBFT_LIB): force_libft
	make -C $(BONUS_LIBFT_DIR)

force_libft:
	@true

# Build mandatory executable
$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

# Build bonus executable
$(BONUS_NAME): $(BONUS_OBJ) $(BONUS_LIBFT_LIB)
	$(CC) $(BONUS_OBJ) $(BONUS_LIBFT_LIB) $(LDFLAGS) -o $(BONUS_NAME)

# Compile mandatory object files
mandatory/%.o: mandatory/%.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile bonus object files
bonus/%.o: bonus/%.c $(BONUS_ALL_HEADERS)
	$(CC) $(BONUS_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BONUS_OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(BONUS_LIBFT_DIR)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(BONUS_LIBFT_DIR)

re: fclean all

re_bonus: fclean bonus

.PHONY: clean force_libft
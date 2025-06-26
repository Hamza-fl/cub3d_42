NAME = cub3d
CC = cc 
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
HEADER = includes/cub3d.h 
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)

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
		src/main.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

force_libft:
	@true

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(FLAGS) -lreadline $(OBJ) $(LIBFT_LIB) -o $(NAME)

%.o: %.c $(ALL_HEADERS)
	$(CC) $(FLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re force_libft
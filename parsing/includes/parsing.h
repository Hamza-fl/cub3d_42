#ifndef PARSING_H
#define PARSING_H

#include "cub3d.h"
#include "get_next_line.h"

# define RED    "\x1b[31m"
# define RESET  "\x1b[0m"

////////////Parsing_utils
bool    is_texture_line(const char *line);
bool    line_is_empty(const char *line);
void    init_parsing(t_parsing *p);
void    print_error(const char *msg);
void	ft_free_split(char **split);
bool	set_texture_path(char *line, t_parsing *p);
bool    file_has_xpm_extension(const char *path);
bool    set_ceiling_color(char *line, t_parsing *p);
bool    set_floor_color(char *line, t_parsing *p);
bool    ft_str_isnumeric(const char *s);
bool    split_rgb(const char *s, int rgb[3]);
bool    parse_header(int fd, t_parsing *parsing, char **first_line);
bool    collect_map_lines(int fd, char *first_line, char ***out_lines, int *num_lines);
bool    validate_map(char **map_lines, int height, int width, t_parsing *p);
bool    allocate_map_matrix(char **raw_map_lines, int map_line_count, int max_width, t_parsing *p);
bool    parse_map_and_allocate(int fd, char *first_map_line, t_parsing *p);
bool    ft_parsing(const char *filename, t_parsing *parsing);

////////////libft_func

int     ft_atoi(const char *str);
void	*ft_malloc(size_t size, int mode);
char	**ft_split(char const *s, char c);
int     ft_strcmp(const char *s1, const char *s2);
void    *ft_memcpy(void *dest, const void *src, size_t n);
char    *ft_strdup(const char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);

#endif
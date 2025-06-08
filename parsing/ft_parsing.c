#include "includes/parsing.h"

bool    ft_parsing(const char *filename, t_parsing *parsing)
{
    int         fd;
    t_parsing   tmp;
    char        *first_line;

    first_line = NULL;
	init_parsing(&tmp);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
		return (print_error("Error\nCannot open .cub file\n"), false);
    if (!parse_header(fd, &tmp, &first_line))
        return (close(fd), false);
	if (!parse_map_and_allocate(fd, first_line, &tmp))
        return (close(fd), false);
	close(fd);
    *parsing = tmp;
    return (true);
}
#include "../includes/parsing.h"

static char *read_next_nonempty_line(int fd)
{
    char    *line;

    line = get_next_line(fd);
    while (line && line_is_empty(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

static bool process_header_line(char *line, t_parsing *p, 
        int *header_count, char **first_map_line)
{

    if (is_texture_line(line))
    {
        if (!set_texture_path(line, p))
        {
            (free(line), ft_malloc(0, 0));
            return (false);
        }
        (*header_count)++;
        free(line);
    }
    else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
    {
        if (!set_floor_color(line, p))
        {
            (free(line), ft_malloc(0, 0));
            return (false);
        }
        (*header_count)++;
        free(line);
    }
    else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
    {
        if (!set_ceiling_color(line, p))
        {
            (free(line), ft_malloc(0, 0));
            return false;
        }
        (*header_count)++;
        free(line);
    }
    else
        *first_map_line = line;
    return (true);
}

bool    parse_header(int fd, t_parsing *parsing, char **first_line)
{
    char    *line;
    int     header_count;

    header_count = 0;
    *first_line = NULL;
    line = read_next_nonempty_line(fd);
    while (header_count <= 6 && line) // <= for the last if i have by exmple empty string
    {
        if (!process_header_line(line , parsing, &header_count, first_line))
            return (false);
        if (*first_line)
            break;
        line = read_next_nonempty_line(fd);
    }
    if (header_count < 6)
    {
        print_error("Error\nNot all textures/colors provided.\n");
        if (line)
            free(line);
        ft_malloc(0, 0);
        return (false);
    }
    if (!*first_line)
    {
        print_error("Error\nUnexpected EOF before map.\n");
        if (line)
            free(line);
        ft_malloc(0, 0);
        return false;
    }
    return (true);
}
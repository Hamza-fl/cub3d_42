#include "../includes/parsing.h"

bool allocate_map_matrix(char **raw_map_lines, int map_line_count, int max_width, t_parsing *p)
{
    p->map = ft_malloc(sizeof(char *) * (map_line_count + 1), 1);
    if (!p->map)
    {
        print_error("Error\nFailed to allocate map row pointers.\n");
        ft_malloc(0, 0);
        return false;
    }
    int r = 0;
    while (r < map_line_count)
    {
        int row_len = ft_strlen(raw_map_lines[r]);
        p->map[r] = ft_malloc(sizeof(char) * (max_width + 1), 1);
        if (!p->map[r])
        {
            print_error("Error\nFailed to allocate map row.\n");
            ft_malloc(0, 0);
            return false;
        }
        ft_memcpy(p->map[r], raw_map_lines[r], row_len);
        int c = row_len;
        while (c < max_width)
        {
            p->map[r][c] = ' ';
            c++;
        }
        p->map[r][max_width] = '\0';
        r++;
    }
    p->map[map_line_count] = NULL;
    p->map_width           = max_width;//check
    p->map_height          = map_line_count;
    return true;
}
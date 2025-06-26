#include "../../includes/cub3d.h"

bool trim_map_lines(char **map_lines, int height)
{
    char *trimmed_line;
    for (int i = 0; i < height; i++)
    {
        trimmed_line = ft_strtrim(map_lines[i], " \t\n\r\f\v");
        if (!trimmed_line)
            return false; // ft_malloc failure in ft_strtrim
        free(map_lines[i]);
        map_lines[i] = trimmed_line;
    }
    return true;
}

static bool  check_basic_args(char **map_lines, int height, int width, t_parsing *p)
{
    if (!map_lines || height <= 0 || width <= 0 || !p)
        return false;
    return true;
}

static bool  find_max_width_and_check_lengths(char **map_lines,
                                              int height,
                                              int width)
{
    int r = 0;
    while (r < height)
    {
        int len = ft_strlen(map_lines[r]);
        if (len > width)
        {
            print_error("Error\nMap line length exceeds width \n");
            return false;
        }
        r++;
    }
    return true;
}

static bool  scan_and_locate_player(char **map_lines,
                                     int height,
                                     int width,
                                     t_parsing *p)
{
    bool player_found = false;
    int   r = 0;
    char ch;

    while (r < height)
    {
        int len = ft_strlen(map_lines[r]);
        int c   = 0;

        while (c < width)
        {
            if (c < len)
                ch = map_lines[r][c];
            else 
                ch = ' ';
            if (ch != '0' && ch != '1' && ch != ' ' &&
                ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
            {
                print_error("Error\nInvalid character\n");
                return false;
            }
            if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
            {
                if (player_found)
                {
                    print_error("Error\nMultiple player starting positions found\n");
                    return false;
                }
                player_found      = true;
                p->player_dir     = ch;
                p->player_pos.x   = c + 0.5;
                p->player_pos.y   = r + 0.5;//check why 0.5 exactly
            }
            if ((r == 0 || r == height - 1 || c == 0 || c == width - 1) &&
                (ch == '0' || ch == 'N' || ch == 'S' ||
                 ch == 'E' || ch == 'W'))
            {
                print_error("Error\nMap not closed by walls\n");
                return false;
            }
            c++;
        }
        r++;
    }
    if (!player_found)
    {
        print_error("Error\nNo player starting position found in map\n");
        return false;
    }
    return true;
}

static bool check_interior_leaks(char **map_lines, int height, int width)
{
    int r = 1;
    while (r < height - 1)
    {
        int len   = ft_strlen(map_lines[r]);
        int c     = 1;

        while (c < width - 1)
        {
            char ch;
            if (c < len)
                ch = map_lines[r][c];
            else
                ch = ' ';

            if (ch == '0' || ch == 'N' || ch == 'S' ||
                ch == 'E' || ch == 'W')
            {
                char left;
                if (c - 1 < len)
                    left = map_lines[r][c - 1];
                else
                    left = ' ';
                char right;
                if (c + 1 < len)
                    right = map_lines[r][c + 1];
                else
                    right = ' ';
                char up;
                if (r - 1 >= 0)
                {
                    int len_up = ft_strlen(map_lines[r - 1]);
                    if (c < len_up)
                        up = map_lines[r - 1][c];
                    else
                        up = ' ';
                }
                else
                    up = ' ';
                char down;
                if (r + 1 < height)
                {
                    int len_down = ft_strlen(map_lines[r + 1]);
                    if (c < len_down)
                        down = map_lines[r + 1][c];
                    else
                        down = ' ';
                }
                else
                    down = ' ';
                if (left == ' ' || right == ' ' || up == ' ' || down == ' ')
                {
                    print_error("Error\nMap leak detected\n");
                    return false;
                }
            }
            c++;
        }
        r++;
    }
    return true;
}

bool validate_map(char **map_lines, int height, int width, t_parsing *p)
{
    if (!trim_map_lines(map_lines, height))
        return false; //check in each case
    if (!check_basic_args(map_lines, height, width, p))
        return false;
    if (!find_max_width_and_check_lengths(map_lines, height, width))
        return false;
    if (!scan_and_locate_player(map_lines, height, width, p))
        return false;
    if (!check_interior_leaks(map_lines, height, width))//check
        return false;
    p->map_width  = width;
    p->map_height = height;//check
    return (true);
}
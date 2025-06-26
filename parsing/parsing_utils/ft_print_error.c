#include "../../includes/cub3d.h"

void    print_error(const char *msg)
{
    if (!msg)
        return;
    write(2, RED, ft_strlen(RED));
    write(2, msg, ft_strlen(msg));
    write(2, RESET, ft_strlen(RESET));
}

void    init_parsing(t_parsing *p)
{
	if (!p)
		return ;
	p->no_texture    = NULL;
	p->so_texture    = NULL;
	p->we_texture    = NULL;
	p->ea_texture    = NULL;
	p->floor_color   = -1;
	p->ceiling_color = -1;
	p->map           = NULL;
	p->map_width     = 0;
	p->map_height    = 0;
	p->player_pos.x  = 0.0;
	p->player_pos.y  = 0.0;
	p->player_dir    = '\0';
}

bool line_is_empty(const char *line)
{
    size_t i;

    if (!line)
        return true;
    i = 0;
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r' || line[i] == '\f' || line[i] == '\v')
        i++;
    return (line[i] == '\0');
}

bool    is_texture_line(const char *line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (true);
	return (false);
}
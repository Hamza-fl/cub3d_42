#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
// # include "mlx.h"

typedef struct s_vector {
    double x;
    double y;
} t_vector;

typedef struct s_parsing {
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     floor_color;
    int     ceiling_color;
    char    **map;
    int     map_width; // width same thing 
    int     map_height; // handle max len of mac
    t_vector player_pos;
    char    player_dir;
} t_parsing;

typedef struct s_player {
    t_vector pos;
    t_vector dir;
    t_vector plane;
} t_player;

typedef struct s_ray {
    t_vector ray_dir;
    t_vector side_dist;
    t_vector delta_dist;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    double perp_wall_dist;
} t_ray;

typedef struct s_game {
    void        *mlx;
    void        *win;
    int         screen_width;
    int         screen_height;

    void        *textures[4];   // NO, SO, WE, EA
    int         floor_color;
    int         ceiling_color;

    char        **map;
    int         map_width;
    int         map_height;

    t_player    player;
    t_ray       ray;
} t_game;

typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;

typedef struct s_line_node
{
    char                *line;
    struct s_line_node  *next;
}   t_line_node;

#endif
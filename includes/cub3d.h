#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../minilibx-linux/mlx.h"

// Key codes (X11)
#define KEY_ESC    65307
#define KEY_W      119
#define KEY_S      115
#define KEY_A       97
#define KEY_D      100
#define KEY_LEFT  65361
#define KEY_RIGHT 65363

typedef struct s_vector {
    double x;
    double y;
} t_vector;

// Parsing struct
typedef struct s_parsing {
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     floor_color;
    int     ceiling_color;
    char    **map;
    int     map_width;
    int     map_height;
    t_vector player_pos;
    char    player_dir;
} t_parsing;

// Player struct
typedef struct s_player {
    t_vector pos;
    t_vector dir;
    t_vector plane;
} t_player;

// Ray struct
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

// Main game struct
typedef struct s_game {
    void        *mlx;
    void        *win;
    int         screen_width;
    int         screen_height;

    // Raw MLX textures and their pixel data
    void        *mlx_text_img[4];
    char        *tex_data[4];
    int         tex_width[4];
    int         tex_height[4];
    int         tex_bpp[4];
    int         tex_line_len[4];
    int         tex_endian[4];

    int         floor_color;
    int         ceiling_color;

    char        **map;
    int         map_width;
    int         map_height;

    t_player    player;
    t_ray       ray;

    // Off-screen buffer
    void        *img;
    char        *img_data;
    int         bpp;
    int         stride;
    int         endian;
} t_game;

// Function prototypes
t_parsing   *parse_cub_file(const char *filename);
void        init_game_from_parsing(t_game *g, t_parsing *p);
void        raycast_frame(t_game *g);
bool    ft_parsing(const char *filename, t_parsing *parsing);

#endif
#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <mlx.h>
#include <fcntl.h>

# define RED    "\x1b[31m"
# define RESET  "\x1b[0m"

//for the parsing
typedef struct s_line_node
{
	char				*line;
	struct s_line_node	*next;
} t_line_node;

#define KEY_ESC    53
#define KEY_W      13
#define KEY_S      1
#define KEY_A      0
#define KEY_D      2
#define KEY_LEFT   123
#define KEY_RIGHT  124

// Constants for better code readability
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEX_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

// Texture indices
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define WEST_TEX 2
# define EAST_TEX 3

typedef struct s_vector {
	double x;
	double y;
} t_vector;

typedef struct s_parsing {
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_vector	player_pos;
	char		player_dir;
} t_parsing;

// Enhanced texture structure for better management
typedef struct s_texture {
	void    *img;           // MLX image pointer
	char    *data;          // Raw pixel data
	int     width;          // Texture width
	int     height;         // Texture height
	int     bpp;            // Bits per pixel
	int     line_len;       // Line length in bytes
	int     endian;         // Endianness
} t_texture;

// Enhanced player structure with camera plane
typedef struct s_player {
	t_vector    pos;        // Player position
	t_vector    dir;        // Direction vector
	t_vector    plane;      // Camera plane vector
	double      move_speed; // Movement speed
	double      rot_speed;  // Rotation speed
} t_player;

// Enhanced ray structure for DDA algorithm
typedef struct s_ray {
	t_vector    dir;            // Ray direction
	t_vector    side_dist;      // Distance to next x/y side
	t_vector    delta_dist;     // Length of ray from current pos to x/y side
	int         map_x;          // Current map position x
	int         map_y;          // Current map position y
	int         step_x;         // Step direction in x (-1 or 1)
	int         step_y;         // Step direction in y (-1 or 1)
	int         hit;            // Was wall hit?
	int         side;           // NS or EW wall hit?
	double      perp_wall_dist; // Perpendicular wall distance
	int         line_height;    // Height of line to draw
	int         draw_start;     // Start of line to draw
	int         draw_end;       // End of line to draw
	int         tex_num;        // Texture number (0-3)
	double      wall_x;         // Exact position of wall hit
	int         tex_x;          // Texture x coordinate
	double      step;           // How much to increase texture coordinate per screen pixel
	double      tex_pos;        // Starting texture coordinate
} t_ray;

typedef struct s_keys {
	int shot;
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
	int esc;
} t_keys;

// Screen buffer structure for efficient rendering
typedef struct s_image {
	void    *img;       // MLX image pointerw
	char    *data;      // Raw pixel data
	int     bpp;        // Bits per pixel
	int     line_len;   // Line length in bytes
	int     endian;     // Endianness
	int     width;      // Image width
	int     height;     // Image height
} t_image;

typedef struct s_game {
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	t_texture	textures[7];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		ray;
	t_keys		keys;
	t_image		screen;
	// Game state
	int			running;        // Game running flag
	double		frame_time;     // Time of current frame
	double		old_time;       // Time of previous frame
} t_game;

// Function prototypes
bool	ft_parsing(const char *filename, t_parsing *parsing);

////////////Parsing_utils
bool	is_texture_line(const char *line);
bool	line_is_empty(const char *line);
void	init_parsing(t_parsing *p);
void	print_error(const char *msg);
void	ft_free_split(char **split);
bool	set_texture_path(char *line, t_parsing *p);
bool	file_has_xpm_extension(const char *path);
bool	set_ceiling_color(char *line, t_parsing *p);
bool	set_floor_color(char *line, t_parsing *p);
bool	ft_str_isnumeric(const char *s);
bool	split_rgb(const char *s, int rgb[3]);
bool	parse_header(int fd, t_parsing *parsing, char **first_line);
bool	collect_map_lines(int fd, char *first_line, char ***out_lines, int *num_lines);
bool	validate_map(char **map_lines, int height, int width, t_parsing *p);
bool	allocate_map_matrix(char **raw_map_lines, int map_line_count, int max_width, t_parsing *p);
bool	parse_map_and_allocate(int fd, char *first_map_line, t_parsing *p);
bool	ft_parsing(const char *filename, t_parsing *parsing);

//init the game
int	ft_init_game(t_game *game, t_parsing *parsing);
//game loop
int	ft_game_loop(t_game *game);
//clean game
void	cleanup_game(t_game *game);
int		close_game(t_game *game);
//input
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
// update player
void	update_player(t_game *game);
void	cast_rays(t_game *game);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

// inti pos
void	init_ray_dir(t_game *game, int x);
void	init_delta_dist(t_game *game);
void	init_first_step(t_game *game);

//dda
void	perform_dda(t_game *game);

void	calc_player_to_wall(t_game *game);
void	calc_wall_line(t_game *game, int *start, int *end, int *line);
//rotate
void rotate_player(t_game *game, double angle);
void draw_minimap(t_game *game);
#endif
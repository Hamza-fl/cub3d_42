#include "../includes/cub3d.h"

static char *dummy_map[] = {
    "11111",
    "10001",
    "10N01",
    "10001",
    "11111",
    NULL
};

static void init_player_direction(t_player *player, char dir)
{
    if (dir == 'N') { player->dir.x = 0;  player->dir.y = -1; player->plane.x = 0.66; player->plane.y = 0; }
    else if (dir == 'S') { player->dir.x = 0;  player->dir.y =  1; player->plane.x = -0.66; player->plane.y = 0; }
    else if (dir == 'E') { player->dir.x = 1;  player->dir.y =  0; player->plane.x = 0;    player->plane.y = 0.66; }
    else if (dir == 'W') { player->dir.x = -1; player->dir.y =  0; player->plane.x = 0;    player->plane.y = -0.66; }
}

t_parsing *parse_cub_file(const char *filename)
{
    (void)filename;
    t_parsing *p = malloc(sizeof(*p));
    if (!p)
        return NULL;
    p->no_texture     = "./textures/north.xpm";
    p->so_texture     = "./textures/south.xpm";
    p->we_texture     = "./textures/west.xpm";
    p->ea_texture     = "./textures/east.xpm";
    p->floor_color = (0 << 16) | (0 << 8) | 255;   // Blue floor
    p->ceiling_color = (0 << 16) | (255 << 8) | 0; // Green ceiling
    p->map            = dummy_map;
    p->map_width      = 5;
    p->map_height     = 5;
    p->player_pos.x   = 2.5;
    p->player_pos.y   = 2.5;
    p->player_dir     = 'N';
    return p;
}

void init_game_from_parsing(t_game *g, t_parsing *p)
{
    g->screen_width  = 1440;
    g->screen_height = 900;
    g->map           = p->map;
    g->map_width     = p->map_width;
    g->map_height    = p->map_height;
    g->floor_color   = p->floor_color;
    g->ceiling_color = p->ceiling_color;
    g->player.pos    = p->player_pos;
    init_player_direction(&g->player, p->player_dir);
}

// Load textures
static int load_textures(t_game *g, t_parsing *p)
{
    char *texture_paths[4] = {p->no_texture, p->so_texture, p->we_texture, p->ea_texture};
    
    for (int i = 0; i < 4; i++)
    {
        g->mlx_text_img[i] = mlx_xpm_file_to_image(g->mlx, texture_paths[i], 
                                                   &g->tex_width[i], &g->tex_height[i]);
        if (!g->mlx_text_img[i])
        {
            printf("Error: Failed to load texture %s\n", texture_paths[i]);
            return 0;
        }
        
        g->tex_data[i] = mlx_get_data_addr(g->mlx_text_img[i], &g->tex_bpp[i], 
                                          &g->tex_line_len[i], &g->tex_endian[i]);
        if (!g->tex_data[i])
        {
            printf("Error: Failed to get texture data for %s\n", texture_paths[i]);
            return 0;
        }
    }
    return 1;
}

// Initialize MLX and create window
static int init_mlx(t_game *g)
{
    g->mlx = mlx_init();
    if (!g->mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        return 0;
    }
    
    g->win = mlx_new_window(g->mlx, g->screen_width, g->screen_height, "Cub3D");
    if (!g->win)
    {
        printf("Error: Failed to create window\n");
        return 0;
    }
    
    // Create image buffer
    g->img = mlx_new_image(g->mlx, g->screen_width, g->screen_height);
    if (!g->img)
    {
        printf("Error: Failed to create image buffer\n");
        return 0;
    }
    
    g->img_data = mlx_get_data_addr(g->img, &g->bpp, &g->stride, &g->endian);
    if (!g->img_data)
    {
        printf("Error: Failed to get image data address\n");
        return 0;
    }
    
    return 1;
}

// Handle key press events
static int key_press(int keycode, t_game *g)
{
    double move_speed = 0.1;
    double rot_speed = 0.05;
    
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(g->mlx, g->win);
        exit(0);
    }
    else if (keycode == KEY_W)
    {
        // Move forward
        double new_x = g->player.pos.x + g->player.dir.x * move_speed;
        double new_y = g->player.pos.y + g->player.dir.y * move_speed;
        
        if (g->map[(int)new_y][(int)g->player.pos.x] != '1')
            g->player.pos.y = new_y;
        if (g->map[(int)g->player.pos.y][(int)new_x] != '1')
            g->player.pos.x = new_x;
    }
    else if (keycode == KEY_S)
    {
        // Move backward
        double new_x = g->player.pos.x - g->player.dir.x * move_speed;
        double new_y = g->player.pos.y - g->player.dir.y * move_speed;
        
        if (g->map[(int)new_y][(int)g->player.pos.x] != '1')
            g->player.pos.y = new_y;
        if (g->map[(int)g->player.pos.y][(int)new_x] != '1')
            g->player.pos.x = new_x;
    }
    else if (keycode == KEY_A)
    {
        // Strafe left
        double new_x = g->player.pos.x - g->player.plane.x * move_speed;
        double new_y = g->player.pos.y - g->player.plane.y * move_speed;
        
        if (g->map[(int)new_y][(int)g->player.pos.x] != '1')
            g->player.pos.y = new_y;
        if (g->map[(int)g->player.pos.y][(int)new_x] != '1')
            g->player.pos.x = new_x;
    }
    else if (keycode == KEY_D)
    {
        // Strafe right
        double new_x = g->player.pos.x + g->player.plane.x * move_speed;
        double new_y = g->player.pos.y + g->player.plane.y * move_speed;
        
        if (g->map[(int)new_y][(int)g->player.pos.x] != '1')
            g->player.pos.y = new_y;
        if (g->map[(int)g->player.pos.y][(int)new_x] != '1')
            g->player.pos.x = new_x;
    }
    else if (keycode == KEY_LEFT)
    {
        // Rotate left
        double old_dir_x = g->player.dir.x;
        g->player.dir.x = g->player.dir.x * cos(rot_speed) - g->player.dir.y * sin(rot_speed);
        g->player.dir.y = old_dir_x * sin(rot_speed) + g->player.dir.y * cos(rot_speed);
        double old_plane_x = g->player.plane.x;
        g->player.plane.x = g->player.plane.x * cos(rot_speed) - g->player.plane.y * sin(rot_speed);
        g->player.plane.y = old_plane_x * sin(rot_speed) + g->player.plane.y * cos(rot_speed);
    }
    else if (keycode == KEY_RIGHT)
    {
        // Rotate right
        double old_dir_x = g->player.dir.x;
        g->player.dir.x = g->player.dir.x * cos(-rot_speed) - g->player.dir.y * sin(-rot_speed);
        g->player.dir.y = old_dir_x * sin(-rot_speed) + g->player.dir.y * cos(-rot_speed);
        double old_plane_x = g->player.plane.x;
        g->player.plane.x = g->player.plane.x * cos(-rot_speed) - g->player.plane.y * sin(-rot_speed);
        g->player.plane.y = old_plane_x * sin(-rot_speed) + g->player.plane.y * cos(-rot_speed);
    }
    
    // Re-render the frame
    raycast_frame(g);
    return 0;
}

// Handle window close
static int close_window(t_game *g)
{
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return 0;
}

// Main game loop
static int game_loop(t_game *g)
{
    raycast_frame(g);
    return 0;
}

// Cleanup function
static void cleanup_game(t_game *g)
{
    for (int i = 0; i < 4; i++)
    {
        if (g->mlx_text_img[i])
            mlx_destroy_image(g->mlx, g->mlx_text_img[i]);
    }
    if (g->img)
        mlx_destroy_image(g->mlx, g->img);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->mlx)
        mlx_destroy_display(g->mlx);
}

int main(int ac, char **argv)
{
    t_parsing *p;
    t_game g;

    if (!ft_parsing(argv[1], p))
    {
        // print_error("Parsing failed.\n");
        return EXIT_FAILURE;
    }
    
    init_game_from_parsing(&g, p);
    
    // Initialize MLX
    if (!init_mlx(&g))
    {
        free(p);
        return 1;
    }
    
    // Load textures
    if (!load_textures(&g, p))
    {
        cleanup_game(&g);
        free(p);
        return 1;
    }
    
    // Set up event handlers
    mlx_hook(g.win, 2, 1L<<0, key_press, &g);           // Key press
    mlx_hook(g.win, 17, 1L<<17, close_window, &g);      // Window close
    mlx_loop_hook(g.mlx, game_loop, &g);                // Main loop
    
    // Start the main loop
    mlx_loop(g.mlx);
    
    // Cleanup (this won't be reached in normal execution)
    cleanup_game(&g);
    free(p);
    return 0;
}
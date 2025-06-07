#include "../includes/cub3d.h"

// Put pixel in the image buffer
static void put_pixel(t_game *g, int x, int y, int color)
{
    if (x >= 0 && x < g->screen_width && y >= 0 && y < g->screen_height)
    {
        int offset = y * g->stride + x * (g->bpp / 8);
        *(int *)(g->img_data + offset) = color;
    }
}

// Initialize ray for current screen column
static void init_ray(t_game *g, int x)
{
    double camera_x = 2 * x / (double)g->screen_width - 1;
    
    g->ray.ray_dir.x = g->player.dir.x + g->player.plane.x * camera_x;
    g->ray.ray_dir.y = g->player.dir.y + g->player.plane.y * camera_x;
    
    g->ray.map_x = (int)g->player.pos.x;
    g->ray.map_y = (int)g->player.pos.y;
    
    // Calculate delta distances
    if (g->ray.ray_dir.x == 0)
        g->ray.delta_dist.x = 1e30;
    else
        g->ray.delta_dist.x = fabs(1 / g->ray.ray_dir.x);
    
    if (g->ray.ray_dir.y == 0)
        g->ray.delta_dist.y = 1e30;
    else
        g->ray.delta_dist.y = fabs(1 / g->ray.ray_dir.y);
    
    g->ray.hit = 0;
}

// Calculate step and initial side distances
static void calculate_step_and_side_dist(t_game *g)
{
    if (g->ray.ray_dir.x < 0)
    {
        g->ray.step_x = -1;
        g->ray.side_dist.x = (g->player.pos.x - g->ray.map_x) * g->ray.delta_dist.x;
    }
    else
    {
        g->ray.step_x = 1;
        g->ray.side_dist.x = (g->ray.map_x + 1.0 - g->player.pos.x) * g->ray.delta_dist.x;
    }
    
    if (g->ray.ray_dir.y < 0)
    {
        g->ray.step_y = -1;
        g->ray.side_dist.y = (g->player.pos.y - g->ray.map_y) * g->ray.delta_dist.y;
    }
    else
    {
        g->ray.step_y = 1;
        g->ray.side_dist.y = (g->ray.map_y + 1.0 - g->player.pos.y) * g->ray.delta_dist.y;
    }
}

// Perform DDA algorithm
static void perform_dda(t_game *g)
{
    while (g->ray.hit == 0)
    {
        // Jump to next map square, either in x-direction, or in y-direction
        if (g->ray.side_dist.x < g->ray.side_dist.y)
        {
            g->ray.side_dist.x += g->ray.delta_dist.x;
            g->ray.map_x += g->ray.step_x;
            g->ray.side = 0;
        }
        else
        {
            g->ray.side_dist.y += g->ray.delta_dist.y;
            g->ray.map_y += g->ray.step_y;
            g->ray.side = 1;
        }
        
        // Check if ray has hit a wall
        if (g->ray.map_x < 0 || g->ray.map_x >= g->map_width || 
            g->ray.map_y < 0 || g->ray.map_y >= g->map_height ||
            g->map[g->ray.map_y][g->ray.map_x] == '1')
        {
            g->ray.hit = 1;
        }
    }
}

// Calculate distance to wall
static void calculate_distance(t_game *g)
{
    if (g->ray.side == 0)
        g->ray.perp_wall_dist = (g->ray.map_x - g->player.pos.x + (1 - g->ray.step_x) / 2) / g->ray.ray_dir.x;
    else
        g->ray.perp_wall_dist = (g->ray.map_y - g->player.pos.y + (1 - g->ray.step_y) / 2) / g->ray.ray_dir.y;
}

// Get texture number based on wall side
static int get_texture_num(t_game *g)
{
    if (g->ray.side == 0) // North/South walls
    {
        if (g->ray.ray_dir.x > 0)
            return 0; // East texture
        else
            return 2; // West texture
    }
    else // East/West walls
    {
        if (g->ray.ray_dir.y > 0)
            return 1; // South texture
        else
            return 0; // North texture
    }
}

// Get texture color at given coordinates
static int get_texture_color(t_game *g, int tex_num, int tex_x, int tex_y)
{
    if (tex_num < 0 || tex_num >= 4 || !g->tex_data[tex_num])
        return 0xFF0000; // Red color as fallback
    
    if (tex_x < 0 || tex_x >= g->tex_width[tex_num] || 
        tex_y < 0 || tex_y >= g->tex_height[tex_num])
        return 0xFF0000;
    
    int offset = tex_y * g->tex_line_len[tex_num] + tex_x * (g->tex_bpp[tex_num] / 8);
    return *(int *)(g->tex_data[tex_num] + offset);
}

// Draw textured vertical line
static void draw_textured_line(t_game *g, int x, int line_height, int draw_start, int draw_end)
{
    int tex_num = get_texture_num(g);
    
    // Calculate texture x coordinate
    double wall_x;
    if (g->ray.side == 0)
        wall_x = g->player.pos.y + g->ray.perp_wall_dist * g->ray.ray_dir.y;
    else
        wall_x = g->player.pos.x + g->ray.perp_wall_dist * g->ray.ray_dir.x;
    wall_x -= floor(wall_x);
    
    int tex_x = (int)(wall_x * g->tex_width[tex_num]);
    if ((g->ray.side == 0 && g->ray.ray_dir.x > 0) || 
        (g->ray.side == 1 && g->ray.ray_dir.y < 0))
        tex_x = g->tex_width[tex_num] - tex_x - 1;
    
    // Calculate texture step and starting position
    double step = 1.0 * g->tex_height[tex_num] / line_height;
    double tex_pos = (draw_start - g->screen_height / 2 + line_height / 2) * step;
    
    // Draw textured pixels
    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (g->tex_height[tex_num] - 1);
        tex_pos += step;
        
        int color = get_texture_color(g, tex_num, tex_x, tex_y);
        
        // Apply shading for side walls
        if (g->ray.side == 1)
            color = (color >> 1) & 8355711; // Darken by dividing RGB by 2
        
        put_pixel(g, x, y, color);
    }
}

// Draw single ray column
static void draw_ray_column(t_game *g, int x)
{
    // Calculate line height
    int line_height = (int)(g->screen_height / g->ray.perp_wall_dist);
    
    // Calculate draw start and end
    int draw_start = -line_height / 2 + g->screen_height / 2;
    if (draw_start < 0)
        draw_start = 0;
    
    int draw_end = line_height / 2 + g->screen_height / 2;
    if (draw_end >= g->screen_height)
        draw_end = g->screen_height - 1;
    
    // Draw ceiling
    for (int y = 0; y < draw_start; y++)
        put_pixel(g, x, y, g->ceiling_color);
    
    // Draw textured wall
    draw_textured_line(g, x, line_height, draw_start, draw_end);
    
    // Draw floor
    for (int y = draw_end; y < g->screen_height; y++)
        put_pixel(g, x, y, g->floor_color);
}

// Main raycasting function
void raycast_frame(t_game *g)
{
    for (int x = 0; x < g->screen_width; x++)
    {
        // Initialize ray for this column
        init_ray(g, x);
        
        // Calculate step and side distances
        calculate_step_and_side_dist(g);
        
        // Perform DDA
        perform_dda(g);
        
        // Calculate distance
        calculate_distance(g);
        
        // Draw the column
        draw_ray_column(g, x);
    }
    
    // Display the rendered frame
    mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
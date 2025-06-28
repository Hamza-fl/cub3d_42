/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/28 14:15:13 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// // double ft_calcule_last_x(t_game *game, double angle) // angle in rad
// // {
// //     double the_next_x;
// //     double the_next_y;
    
// //     //calculate the first distance
// //     the_next_x = floor(game->player.pos.x);
// //     the_next_y = tan(angle) / the_next_y;
// //     // add unite and calculate the next 
// //     the_next_x = the_next_x + 1; // 62 bit for each unite
// //     the_next_y = tan(angle) / the_next_y;
// //     while () // condition for check if wall
// //     {
// //         the_next_x = the_next_x + 1; // 62 bit for each unite
// //         the_next_y = tan(angle) / the_next_y;
// //     }
// //     return (the_next_x);
// // }

// double ft_calcule_last_x(t_game *game, double angle)
// {
//     // Ray direction vector
//     double ray_dir_x = cos(angle);
//     double ray_dir_y = sin(angle);

//     // Player starting grid cell
//     int map_x = (int)game->player.pos.x;
//     int map_y = (int)game->player.pos.y;

//     // Delta distances
//     double delta_dist_x = fabs(1 / ray_dir_x);
//     double delta_dist_y = fabs(1 / ray_dir_y);

//     // Calculate step and initial side_dist
//     int step_x;
//     int step_y;
//     double side_dist_x;
//     double side_dist_y;

//     if (ray_dir_x < 0) // 1 <= cos(angle) <= 1
//     {
//         step_x = -1;
//         side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;    // (x.first - int(x.first)) * 1/cos() abs
//     }
//     else
//     {
//         step_x = 1;
//         side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
//     }

//     if (ray_dir_y < 0)// 1 <= sin(angle) <= 1
//     {
//         step_y = -1;
//         side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
//     }
//     else
//     {
//         step_y = 1;
//         side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
//     }

//     // DDA loop to find wall
//     int hit = 0;
//     int side;

//     while (!hit)
//     {
//         if (side_dist_x < side_dist_y)
//         {
//             side_dist_x += delta_dist_x;
//             map_x += step_x;
//             side = 0;
//         }
//         else
//         {
//             side_dist_y += delta_dist_y;
//             map_y += step_y;
//             side = 1;
//         }

//         if (game->map[map_y][map_x] == '1')
//             hit = 1;
//     }

//     // Calculate final perpendicular distance to wall
//     double perp_wall_dist;
//     if (side == 0)
//         perp_wall_dist = (map_x - game->player.pos.x + (1 - step_x) / 2) / ray_dir_x;
//     else
//         perp_wall_dist = (map_y - game->player.pos.y + (1 - step_y) / 2) / ray_dir_y;

//     return perp_wall_dist;
// }


// Helper to check if a map cell is wall
static int is_wall(t_game *game, int x, int y)
{
    if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
        return 1; // Outside map treated as wall
    return (game->map[y][x] == '1');
}

// Calculates distance to wall using DDA for one ray angle
static double cast_single_ray(t_game *game, double ray_angle)
{
    double x_intercept, y_intercept;
    double x_step, y_step;
    double next_x, next_y;
    int map_x, map_y;
    int hit = 0;

    double px = game->player.pos.x;
    double py = game->player.pos.y;

    // Vertical grid lines intersection
    if (cos(ray_angle) > 0) //   -1 <= cos() <= 1
        x_intercept = floor(px) + 1.0;
    else
        x_intercept = floor(px);

    y_intercept = py + (x_intercept - px) * tan(ray_angle);

    x_step = (cos(ray_angle) > 0) ? 1.0 : -1.0; // add if 
    y_step = x_step * tan(ray_angle);

    next_x = x_intercept;
    next_y = y_intercept;

    while (!hit)
    {
        map_x = (cos(ray_angle) > 0) ? (int)next_x : (int)next_x - 1;
        map_y = (int)next_y;

        if (is_wall(game, map_x, map_y))
            hit = 1;
        else
        {
            next_x += x_step;
            next_y += y_step;
            if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
                break;
        }
    }

    double dist_vertical = sqrt((next_x - px)*(next_x - px) + (next_y - py)*(next_y - py));

    // Horizontal grid lines intersection
    if (sin(ray_angle) > 0)
        y_intercept = floor(py) + 1.0;
    else
        y_intercept = floor(py);

    x_intercept = px + (y_intercept - py) / tan(ray_angle);

    y_step = (sin(ray_angle) > 0) ? 1.0 : -1.0;
    x_step = y_step / tan(ray_angle);

    next_x = x_intercept;
    next_y = y_intercept;

    hit = 0;
    while (!hit)
    {
        map_x = (int)next_x;
        map_y = (sin(ray_angle) > 0) ? (int)next_y : (int)next_y - 1;

        if (is_wall(game, map_x, map_y))
            hit = 1;
        else
        {
            next_x += x_step;
            next_y += y_step;
            if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
                break;
        }
    }

    double dist_horizontal = sqrt((next_x - px)*(next_x - px) + (next_y - py)*(next_y - py));

    // Return the closer hit distance
    return (dist_vertical < dist_horizontal) ? dist_vertical : dist_horizontal;
}

void draw_vertical_line(t_game *game, int x, int line_height, int color)
{
    int start = (game->screen_height / 2) - (line_height / 2);
    int end = start + line_height;

    if (start < 0) start = 0;
    if (end > game->screen_height) end = game->screen_height;

    int y;

    // Ceiling
    for (y = 0; y < start; y++)
        my_mlx_pixel_put(&game->screen, x, y, game->ceiling_color);

    // Wall slice
    for (; y < end; y++)
        my_mlx_pixel_put(&game->screen, x, y, color);

    // Floor
    for (; y < game->screen_height; y++)
        my_mlx_pixel_put(&game->screen, x, y, game->floor_color);
}


// Main cast_rays function — cast rays for each vertical column
void cast_rays(t_game *game)
{
    double fov = 60.0 * (M_PI / 180.0); // 60 degrees FOV in radians
    double half_fov = fov / 2.0;
    double player_angle = atan2(game->player.dir.y, game->player.dir.x);

    for (int x = 0; x < game->screen_width; x++)
    {
        // Calculate camera_x in [-1, +1]
        double camera_x = 2.0 * x / (double)game->screen_width - 1.0;

        // Calculate ray angle relative to player direction
        double ray_angle = player_angle + camera_x * half_fov;

        // Cast single ray
        double dist = cast_single_ray(game, ray_angle);

        // Fisheye fix: project the distance to the camera plane
        double corrected_dist = dist * cos(ray_angle - player_angle);
        if (corrected_dist < 0.0001)
            corrected_dist = 0.0001; // avoid div by zero

        // Calculate wall height
        int line_height = (int)(game->screen_height / corrected_dist);

        // Draw the column
        draw_vertical_line(game, x, line_height, 0xFFFFFF);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:04:45 by asebban           #+#    #+#             */
/*   Updated: 2025/07/08 17:39:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


#define MINI_MAP_WINDOW_WIDTH  20
#define MINI_MAP_WINDOW_HEIGHT 20
#define MINI_TILE_SIZE 5
#define MINI_MAP_OFFSET_X 10
#define MINI_MAP_OFFSET_Y 10


void draw_square(t_image *img, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_mlx_pixel_put(img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_minimap_player(t_game *game)
{
    int px = MINI_MAP_OFFSET_X + (int)(game->player.pos.x * MINI_TILE_SIZE);
    int py = MINI_MAP_OFFSET_Y + (int)(game->player.pos.y * MINI_TILE_SIZE);

    draw_square(&game->screen, px - 2, py - 2, 4, 0xFF0000); // Red dot  && -2 for centre the player 
}



void draw_minimap(t_game *game)
{
    int player_tile_x;
    int player_tile_y;

    player_tile_x = (int)game->player.pos.x;
    player_tile_y = (int)game->player.pos.y;
    int window_start_x = player_tile_x - MINI_MAP_WINDOW_WIDTH / 2;
    int window_start_y = player_tile_y - MINI_MAP_WINDOW_HEIGHT / 2;

    int y = 0;
    int x = 0;
    while (y < MINI_MAP_WINDOW_HEIGHT)
    {
        x = 0;
        while (x < MINI_MAP_WINDOW_WIDTH)
        {
            int map_x = window_start_x + x;
            int map_y = window_start_y + y;

            if (map_x >= 0 && map_x < game->map_width &&
                map_y >= 0 && map_y < game->map_height &&
                game->map[map_y][map_x] == '1')
            {
                int sx = MINI_MAP_OFFSET_X + x * MINI_TILE_SIZE;
                int sy = MINI_MAP_OFFSET_Y + y * MINI_TILE_SIZE;

                draw_square(&game->screen, sx, sy, MINI_TILE_SIZE, 0xFFFFFF);
            }
            x++;
        }
        y++;
    }
    int px = MINI_MAP_OFFSET_X + (MINI_MAP_WINDOW_WIDTH / 2) * MINI_TILE_SIZE;
    int py = MINI_MAP_OFFSET_Y + (MINI_MAP_WINDOW_HEIGHT / 2) * MINI_TILE_SIZE;

    draw_square(&game->screen, px - 2, py - 2, 4, 0xFF0000);
}

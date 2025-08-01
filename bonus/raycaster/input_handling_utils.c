/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:42:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/01 08:05:02 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int find_nearest_door(t_game *game, int *door_x, int *door_y)
{
    int player_x = (int)game->player.pos.x;
    int player_y = (int)game->player.pos.y;
    float interaction_range = 1.5; // Adjust this value as needed
    
    // Check surrounding tiles within interaction range
    for (int dy = -2; dy <= 2; dy++)
    {
        for (int dx = -2; dx <= 2; dx++)
        {
            int check_x = player_x + dx;
            int check_y = player_y + dy;
            
            // Check if position is within bounds and is a door
            if (check_x >= 0 && check_x < game->map_width && 
                check_y >= 0 && check_y < game->map_height &&
                game->map[check_y][check_x] == 'D')
            {
                // Calculate distance
                float dist = sqrt((dx * dx) + (dy * dy));
                if (dist <= interaction_range)
                {
                    *door_x = check_x;
                    *door_y = check_y;
                    return 1; // Found a door
                }
            }
        }
    }
    return 0; // No door found in range
}

int player_inside_door(t_game *game, int door_x, int door_y)
{
    return (game->player.pos.x >= door_x && 
            game->player.pos.x <= door_x + 1 &&
            game->player.pos.y >= door_y && 
            game->player.pos.y <= door_y + 1);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_F)
	{
		int door_x, door_y;
		if (find_nearest_door(game, &door_x, &door_y))
		{
			if (game->door_status[door_y][door_x] == 0)
				game->door_status[door_y][door_x] = 1;
			else if (game->door_status[door_y][door_x] == 1)
			{
				if (!player_inside_door(game, door_x, door_y))
					game->door_status[door_y][door_x] = 0;
			}
		}
	}
	if (keycode == 14)
		game->keys.shot = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

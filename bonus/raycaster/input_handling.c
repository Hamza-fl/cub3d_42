/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/09 15:29:43 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 14)
		game->keys.shot = 1;
	else if (keycode == KEY_W)
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
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 14)
		game->keys.shot = 0;
	else if (keycode == KEY_W)
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

void rotate_player(t_game *game, double angle)
{
	double old_dir_x = game->player.dir.x;
	double old_plane_x = game->player.plane.x;
	
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
	
	game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
}

void	update_player(t_game *game)
{
	t_vector	new_pos;

	if (game->keys.w)
	{
		new_pos.x = game->player.pos.x + game->player.dir.x * game->player.move_speed;
		new_pos.y = game->player.pos.y + game->player.dir.y * game->player.move_speed;
		if (game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x - 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x - 0.05)] != '1')
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (game->keys.s)
	{
		new_pos.x = game->player.pos.x - game->player.dir.x * game->player.move_speed;
		new_pos.y = game->player.pos.y - game->player.dir.y * game->player.move_speed;
		if (game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x - 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x - 0.05)] != '1')
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (game->keys.a)
	{
		new_pos.x = game->player.pos.x - game->player.plane.x * game->player.move_speed;
		new_pos.y = game->player.pos.y - game->player.plane.y * game->player.move_speed;
		if (game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x - 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x - 0.05)] != '1')
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (game->keys.d)
	{
		new_pos.x = game->player.pos.x + game->player.plane.x * game->player.move_speed;
		new_pos.y = game->player.pos.y + game->player.plane.y * game->player.move_speed;
		if (game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y + 0.05)][(int)(new_pos.x - 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x + 0.05)] != '1' &&
		game->map[(int)(new_pos.y - 0.05)][(int)(new_pos.x - 0.05)] != '1')
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (game->keys.right)
		rotate_player(game, game->player.rot_speed);
	if (game->keys.left)
		rotate_player(game, -game->player.rot_speed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:02:03 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/10 10:37:13 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player(t_game *game, t_parsing *parsing)
{
	game->player.pos.x = parsing->player_pos.x;
	game->player.pos.y = parsing->player_pos.y;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	if (parsing->player_dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (parsing->player_dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else if (parsing->player_dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (parsing->player_dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	return (1);
}

int	init_textures(t_game *game, t_parsing *parsing)
{
	char *texture_paths[7];
	int i;
	
	texture_paths[NORTH_TEX] = parsing->no_texture;
	texture_paths[SOUTH_TEX] = parsing->so_texture;
	texture_paths[WEST_TEX] = parsing->we_texture;
	texture_paths[EAST_TEX] = parsing->ea_texture;
	texture_paths[4] = "bonus/textures/weapon_1.xpm";
	texture_paths[5] = "bonus/textures/weapon_2.xpm";
	texture_paths[6] = "bonus/textures/weapon_3.xpm";
	i = 0;
	while (i < 7)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, 
														texture_paths[i],
														&game->textures[i].width,
														&game->textures[i].height);
		if (!game->textures[i].img)
		{
			print_error("Error: Could not load texture\n");
			return (0);
		}
		game->textures[i].data = mlx_get_data_addr(game->textures[i].img,
												  &game->textures[i].bpp,
												  &game->textures[i].line_len,
												  &game->textures[i].endian);
		i++;
	}
	return (1);
}

void init_keys(t_keys *keys)
{
	keys->shot = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

int	ft_init_game(t_game *game, t_parsing *parsing)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->screen_height = SCREEN_HEIGHT;
	game->screen_width = SCREEN_WIDTH;
	game->win = mlx_new_window(game->mlx, game->screen_width, \
									game->screen_height, "Cub3D");
	if (!game->win)
		return (0);
	game->screen.img = mlx_new_image(game->mlx, game->screen_width, \
									game->screen_height);
	if (!game->screen.img)
		return (0);
	game->screen.data = mlx_get_data_addr(game->screen.img, 
									&game->screen.bpp,
									&game->screen.line_len, 
									&game->screen.endian);
	game->screen.width = game->screen_width;
	game->screen.height = game->screen_height;
	game->map = parsing->map;
	game->map_height = parsing->map_height;
	game->map_width = parsing->map_width;
	game->floor_color = parsing->floor_color;
	game->ceiling_color = parsing->ceiling_color;
	if (!init_player(game, parsing))
		return (0);
	if (!init_textures(game, parsing))
		return (0);
	init_keys(&game->keys);
	game->running = 1;
	game->frame_time = 0;
	game->old_time = 0;
	return (1);
}

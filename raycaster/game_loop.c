/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:02:19 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/06 14:37:05 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;
	
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void put_backroad(t_game *game)
{
	int	x;
	int	y;
	int half_heigh;
	
	half_heigh = game->screen_height / 2;
	y = 0;
	while (y < half_heigh)
	{
		x = 0;
		while (x < game->screen_width)
		{
			my_mlx_pixel_put(&game->screen, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			my_mlx_pixel_put(&game->screen, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void put_hands(t_game *game)
{
	if (game->keys.shot == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->textures[4].img, 20, 0);
	static int frame = 0;
	if (game->keys.shot == 1)
	{
		frame++;
		if (frame % 2 == 0)
			mlx_put_image_to_window(game->mlx, game->win, game->textures[5].img, 150, 415);
		else
			mlx_put_image_to_window(game->mlx, game->win, game->textures[6].img, 150, 415);
	}
}

int	ft_game_loop(t_game *game)
{
	if (!game->running)
		return (0);
	update_player(game);
	put_backroad(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	put_hands(game);
	return (0);
}
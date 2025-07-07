/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/07 15:45:35 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int	*buffer;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	buffer = (int *)texture->data;
	return (buffer[y * texture->width + x]);
}

static int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	return (game->map[y][x] == '1');
}

static void	dda_step(t_game *game, int *side)
{
	if (game->ray.side_dist.x < game->ray.side_dist.y)
	{
		game->ray.side_dist.x += game->ray.delta_dist.x;
		game->ray.map_x += game->ray.step_x;
		*side = 0;
	}
	else
	{
		game->ray.side_dist.y += game->ray.delta_dist.y;
		game->ray.map_y += game->ray.step_y;
		*side = 1;
	}
}

void	perform_dda(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	while (!hit)
	{
		dda_step(game, &side);
		if (is_wall(game, game->ray.map_x, game->ray.map_y))
			hit = 1;
	}
	game->ray.hit = hit;
	game->ray.side = side;
}

static void	init_ray_dir(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->screen_width - 1;
	
	game->ray.dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	game->ray.dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	game->ray.map_x = (int)game->player.pos.x;
	game->ray.map_y = (int)game->player.pos.y;
}

static void	init_delta_dist(t_game *game)
{
	if (game->ray.dir.x == 0)
		game->ray.delta_dist.x = 1e30;
	else
		game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	if (game->ray.dir.y == 0)
		game->ray.delta_dist.y = 1e30;
	else
		game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
}

static void	init_step_and_sidedist(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist.x = (game->player.pos.x
				- game->ray.map_x) * game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist.x = (game->ray.map_x + 1.0
				- game->player.pos.x) * game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist.y = (game->player.pos.y
				- game->ray.map_y) * game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist.y = (game->ray.map_y + 1.0
				- game->player.pos.y) * game->ray.delta_dist.y;
	}
}

static void	calc_line_dims(t_game *game, int *start, int *end, int *height)
{
	*height = (int)(game->screen_height / game->ray.perp_wall_dist);
	*start = -(*height) / 2 + game->screen_height / 2;
	if (*start < 0)
		*start = 0;
	*end = *height / 2 + game->screen_height / 2;
	if (*end >= game->screen_height)
		*end = game->screen_height - 1;
}

static int	select_texture(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x > 0)
			return (WEST_TEX);
		return (EAST_TEX);
	}
	if (game->ray.dir.y > 0)
		return (NORTH_TEX);
	return (SOUTH_TEX);
}

int calc_tex_x(t_game *game)
{
    double hit_pos;
    int texture_x;

    if (game->ray.side == 0)
        hit_pos = game->player.pos.y + game->ray.perp_wall_dist * game->ray.dir.y;
    else
        hit_pos = game->player.pos.x + game->ray.perp_wall_dist * game->ray.dir.x;
    hit_pos = hit_pos - (int)hit_pos;
    texture_x = (int)(hit_pos * TEX_SIZE);
	return texture_x;
}



static void	draw_stripe(t_game *g, int x, int tex, int *vals)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * TEX_SIZE / vals[2];
	tex_pos = (vals[0] - g->screen_height / 2 + vals[2] / 2) * step;
	y = vals[0];
	while (y < vals[1])
	{
		tex_y = (int)tex_pos % TEX_SIZE;
		tex_pos += step;
		color = get_texture_pixel(&g->textures[tex], vals[3], tex_y);
		// if (g->ray.side == 1)
		// 	color = (color >> 1) & 89999999999999993;
		my_mlx_pixel_put(&g->screen, x, y, color);
		y++;
	}
}

void	cast_single_ray(t_game *game, int x)
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_num;
	int		tex_x;
	int		vals[4];

	init_ray_dir(game, x);
	init_delta_dist(game);
	init_step_and_sidedist(game);
	perform_dda(game);
	if (game->ray.side == 0)
	{
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos.x
				+ (1 - game->ray.step_x) / 2) / game->ray.dir.x;
	}
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos.y
				+ (1 - game->ray.step_y) / 2) / game->ray.dir.y;
	calc_line_dims(game, &draw_start, &draw_end, &line_height);
	tex_num = select_texture(game);
	tex_x = calc_tex_x(game);
	vals[0] = draw_start;
	vals[1] = draw_end;
	vals[2] = line_height;
	vals[3] = tex_x;
	draw_stripe(game, x, tex_num, vals);
}


void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->screen_width + 1)
	{
		cast_single_ray(game, x);
		x++;
	}
}
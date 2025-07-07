/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:09:45 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/07 11:09:53 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_player_to_wall(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos.x
			+ (1 - game->ray.step_x)/ 2) / game->ray.dir.x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos.y
			+ (1 - game->ray.step_y) / 2) / game->ray.dir.y;
}

void	calc_wall_line(t_game *game, int *start, int *end, int *line)
{
	*line = (int)(game->screen_height / game->ray.perp_wall_dist);
	*start = -(*line) / 2 + game->screen_height / 2;
	if (*start < 0)
		*start = 0;
	*end = *line / 2 + game->screen_height / 2;
	if (*end >= game->screen_height)
		*end = game->screen_height - 1;
}

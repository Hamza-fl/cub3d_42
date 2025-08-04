/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/04 00:49:43 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	game->running = 0;
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 15)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
}

void	clean_map_tex(t_game *game, t_parsing *parsing)
{
	int	i;

	if (!game)
		return ;
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (parsing)
	{
		if (parsing->we_texture)
			free(parsing->we_texture);
		if (parsing->no_texture)
			free(parsing->no_texture);
		if (parsing->so_texture)
			free(parsing->so_texture);
		if (parsing->ea_texture)
			free(parsing->ea_texture);
	}
}

void	free_door_status(t_game *game, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(game->door_status[i]);
		i++;
	}
	free(game->door_status);
	game->door_status = NULL;
}

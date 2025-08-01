/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/01 08:08:37 by hfalati          ###   ########.fr       */
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
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
	if (game->screen.img)
	{
		mlx_destroy_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	if (game->win) 
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	free(game->mlx);
	game->mlx = NULL;
}

void clean_map_tex(t_game *game, t_parsing *parsing)
{
    int i;

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
        game->map = NULL;
    }
	if (parsing)
    {
        if (parsing->we_texture)
        {
            free(parsing->we_texture);
            parsing->we_texture = NULL;
        }
        if (parsing->no_texture)
        {
            free(parsing->no_texture);
            parsing->no_texture = NULL;
        }
        if (parsing->so_texture)
        {
            free(parsing->so_texture);
            parsing->so_texture = NULL;
        }
        if (parsing->ea_texture)
        {
            free(parsing->ea_texture);
            parsing->ea_texture = NULL;
        }
	}
}

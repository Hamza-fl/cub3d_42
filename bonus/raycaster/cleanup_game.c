/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/10 14:56:40 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int close_game(t_game *game)
{
    game->running = 0;
    cleanup_game(game);
    exit(EXIT_SUCCESS);
    return (0);
}

void	cleanup_game(t_game *game)
{
	int	i;
	
	i = 0;
	while (i < 8)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// if (game->mlx)
	// {
	// 	mlx_destroy_display(game->mlx);
	// 	free(game->mlx);
	// }
}

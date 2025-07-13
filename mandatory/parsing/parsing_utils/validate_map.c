/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:28 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:28 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool  scan_and_locate_player(char **map_lines,
									 int height,
									 int width,
									 t_parsing *p)
{
	bool player_found = false;
	int   r = 0;
	char ch;

	while (r < height)
	{
		int len = ft_strlen(map_lines[r]);
		int c   = 0;

		while (c < width)
		{
			if (c < len)
				ch = map_lines[r][c];
			else 
				ch = ' ';
			if (ch != '0' && ch != '1' && ch != ' ' &&
				ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
			{
				print_error("Error\nInvalid character\n");
				return false;
			}
			if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
			{
				if (player_found)
				{
					print_error("Error\nMultiple player starting positions found\n");
					return false;
				}
				player_found      = true;
				p->player_dir     = ch;
				p->player_pos.x   = c + 0.5;
				p->player_pos.y   = r + 0.5;//check why 0.5 exactly
			}
			if ((r == 0 || r == height - 1 || c == 0 || c == width - 1) &&
				(ch == '0' || ch == 'N' || ch == 'S' ||
				 ch == 'E' || ch == 'W'))
			{
				print_error("Error\nMap not closed by walls\n");
				return false;
			}
			c++;
		}
		r++;
	}
	if (!player_found)
	{
		print_error("Error\nNo player starting position found in map\n");
		return false;
	}
	return true;
}

bool check_interior_leaks(char **map_lines, int height, int width)
{
	int r = 1;
	while (r < height - 1)
	{
		int len   = ft_strlen(map_lines[r]);
		int c     = 1;

		while (c < width - 1)
		{
			char ch;
			if (c < len)
				ch = map_lines[r][c];
			else
				ch = ' ';

			if (ch == '0' || ch == 'N' || ch == 'S' ||
				ch == 'E' || ch == 'W')
			{
				char left;
				if (c - 1 < len)
					left = map_lines[r][c - 1];
				else
					left = ' ';
				char right;
				if (c + 1 < len)
					right = map_lines[r][c + 1];
				else
					right = ' ';
				char up;
				if (r - 1 >= 0)
				{
					int len_up = ft_strlen(map_lines[r - 1]);
					if (c < len_up)
						up = map_lines[r - 1][c];
					else
						up = ' ';
				}
				else
					up = ' ';
				char down;
				if (r + 1 < height)
				{
					int len_down = ft_strlen(map_lines[r + 1]);
					if (c < len_down)
						down = map_lines[r + 1][c];
					else
						down = ' ';
				}
				else
					down = ' ';
				if (left == ' ' || right == ' ' || up == ' ' || down == ' ')
				{
					print_error("Error\nMap leak detected\n");
					return false;
				}
			}
			c++;
		}
		r++;
	}
	return true;
}


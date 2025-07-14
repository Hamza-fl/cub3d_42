/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:20 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:20 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_door_valid(char **map_lines, int x, int y)
{
	bool	horizontal_ok;
	bool	vertical_ok;

	1 && (horizontal_ok = false, vertical_ok = false);
	if (map_lines[y][x - 1] == '1' && map_lines[y][x + 1] == '1')
		horizontal_ok = true;
	if (map_lines[y - 1][x] == '1' && map_lines[y + 1][x] == '1')
		vertical_ok = true;
	if (!horizontal_ok && !vertical_ok)
		return (print_error("Error: Door is not between two walls!\n"), false);
	return (true);
}

bool	ft_parsing(const char *filename, t_parsing *parsing)
{
	int			fd;
	t_parsing	tmp;
	char		*first_line;

	first_line = NULL;
	ft_initialisation(&tmp);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nCannot open .cub file\n"), false);
	if (!parse_header(fd, &tmp, &first_line))
		return (close(fd), false, ft_malloc(0, 0));
	if (!parse_map_and_allocate(fd, first_line, &tmp))
		return (close(fd), false, ft_malloc(0, 0));
	close(fd);
	*parsing = tmp;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:21 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:21 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	allocate_single_map_row(char **raw_map_lines,
		int row, int max_width, t_parsing *p)
{
	int	row_len;
	int	c;

	row_len = ft_strlen(raw_map_lines[row]);
	p->map[row] = ft_malloc(sizeof(char) * (max_width + 1), 1);
	if (!p->map[row])
	{
		print_error("Error\nFailed to allocate map row.\n");
		return (ft_malloc(0, 0), false);
	}
	ft_memcpy(p->map[row], raw_map_lines[row], row_len);
	c = row_len;
	while (c < max_width)
		1 && (p->map[row][c] = ' ', c++);
	1 && (p->map[row][max_width] = '\0');
	return (true);
}

bool	allocate_map_matrix(char **raw_map_lines,
		int map_line_count, int max_width, t_parsing *p)
{
	int	r;

	1 && (r = 0, p->map = ft_malloc(sizeof(char *) * (map_line_count + 1), 1));
	if (!p->map)
	{
		print_error("Error\nFailed to allocate map row pointers.\n");
		return (ft_malloc(0, 0), false);
	}
	while (r < map_line_count)
	{
		if (!allocate_single_map_row(raw_map_lines, r, max_width, p))
			return (false);
		r++;
	}
	p->map[map_line_count] = NULL;
	1 && (p->map_width = max_width, p->map_height = map_line_count);
	return (true);
}

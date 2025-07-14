/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:00 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:00 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	char	*read_next_nonempty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line_is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static bool	handle_texture_line(char *line, t_parsing *p, int *header_count)
{
	if (!set_texture_path(line, p))
	{
		free(line);
		ft_malloc(0, 0);
		return (false);
	}
	(*header_count)++;
	free(line);
	return (true);
}

static bool	handle_color_line(char *line, t_parsing *p, int *header_count)
{
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (!set_floor_color(line, p))
		{
			free(line);
			ft_malloc(0, 0);
			return (false);
		}
	}
	else
	{
		if (!set_ceiling_color(line, p))
		{
			free(line);
			ft_malloc(0, 0);
			return (false);
		}
	}
	(*header_count)++;
	free(line);
	return (true);
}

static bool	process_header_line(char *line, t_parsing *p,
			int *header_count, char **first_map_line)
{
	if (is_texture_line(line))
		return (handle_texture_line(line, p, header_count));
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (handle_color_line(line, p, header_count));
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (handle_color_line(line, p, header_count));
	else
	{
		*first_map_line = line;
		return (true);
	}
}

bool	parse_header(int fd, t_parsing *parsing, char **first_line)
{
	char	*line;
	int		header_count;

	1 && (header_count = 0, *first_line = NULL);
	line = read_next_nonempty_line(fd);
	while (header_count <= 6 && line)
	{
		if (!process_header_line(line, parsing, &header_count, first_line))
			return (false);
		if (*first_line)
			break ;
		line = read_next_nonempty_line(fd);
	}
	if (header_count < 6)
	{
		print_error("Error\nNot all textures/colors provided.\n");
		return (free(line), ft_malloc(0, 0), false);
	}
	if (!*first_line)
	{
		print_error("Error\nUnexpected EOF before map.\n");
		return (free(line), ft_malloc(0, 0), false);
	}
	return (true);
}

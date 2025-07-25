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

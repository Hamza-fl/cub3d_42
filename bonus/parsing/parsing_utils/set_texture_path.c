/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:41 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:41 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static bool	assign_texture(char **dest, const char *path)
{
	char	*trimmed;
	int		fd;

	if (*dest != NULL)
		return (print_error("Error\nDuplicate texture path\n"), false);
	trimmed = ft_strtrim(path, " \t\r\n");
	if (!trimmed)
		return (print_error("Error\nft_strtrim failed\n"), false);
	if (!file_has_xpm_extension(trimmed))
	{
		(print_error("Error\nTexture missing \".xpm\"\n"), free(trimmed));
		return (false);
	}
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nCannot open texture file\n"), false);
	close(fd);
	*dest = ft_strdup(trimmed);
	free(trimmed);
	if (!*dest)
		return (print_error("Error\nft_strdup failed"), false);
	return (true);
}

bool	set_texture_path(char *line, t_parsing *p)
{
	char	**tokens;
	bool	ok;

	ok = false;
	if (!line || !p)
		return (false);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2] != NULL)
	{
		print_error("Error\nBad texture format\n");
		ft_free_split(tokens);
		return (false);
	}
	if (ft_strcmp(tokens[0], "NO") == 0)
		ok = assign_texture(&p->no_texture, tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		ok = assign_texture(&p->so_texture, tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		ok = assign_texture(&p->we_texture, tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		ok = assign_texture(&p->ea_texture, tokens[1]);
	else
		print_error("Error\nUnknown texture identifier\n");
	ft_free_split(tokens);
	return (ok);
}

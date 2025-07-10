/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:50 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:50 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool set_floor_color(char *line, t_parsing *p)
{
    char *ptr;
    int   rgb[3];

    if (!line || !p)
        return (false);

    if (p->floor_color != -1)
    {
        print_error("Error\nDuplicate floor color line.\n");
        return (false);
    }
    ptr = line + 1;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    if (!split_rgb(ptr, rgb))
        return (false);
    p->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    return (true);
}

bool set_ceiling_color(char *line, t_parsing *p)
{
    char *ptr;
    int   rgb[3];

    if (!line || !p)
        return (false);

    if (p->ceiling_color != -1)
    {
        print_error("Error\nDuplicate ceiling color line.\n");
        return (false);
    }

    ptr = line + 1;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;

    if (!split_rgb(ptr, rgb))
        return (false);

    p->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    return (true);
}

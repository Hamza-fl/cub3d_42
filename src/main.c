/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:39:09 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/24 11:39:09 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **argv)
{
    t_parsing p;
    t_game g;

    if (ac != 2)
    {
        print_error("Error :Usage: ./cub3D <map.cub>\n");
        return (EXIT_FAILURE);
    }
    if (!ft_parsing(argv[1], &p))
    {
        print_error("Error :Parsing failed\n");
        return (EXIT_FAILURE);
    }
}

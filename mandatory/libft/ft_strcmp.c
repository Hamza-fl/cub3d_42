/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:20:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/26 20:20:31 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;
    unsigned char uc1;
    unsigned char uc2;

    while (s1[i] && s1[i] == s2[i])
        i++;

    uc1 = (unsigned char)s1[i];
    uc2 = (unsigned char)s2[i];
    return (int)(uc1 - uc2);
}
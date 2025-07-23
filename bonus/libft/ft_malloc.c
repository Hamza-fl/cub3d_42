/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:17:02 by asebban           #+#    #+#             */
/*   Updated: 2025/07/23 20:54:54 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    free_all(t_collect **head)
{
    t_collect    *current;
    t_collect    *next;

    if (!head || !*head)
        return;

    current = *head;
    while (current)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    *head = NULL;
}

void    *ft_malloc(size_t size, int    mode)
{
    static t_collect    *head;
    t_collect            *node;
    void *data;

    if (mode == 1)
    {
        data = malloc(size);
        if (!data)
        {
            perror("cub3d");
            ft_malloc(0, 0);
            return NULL;
        }

        node = malloc(sizeof(t_collect));
        if (!node)
        {
            free(data);
            perror("cub3d");
            ft_malloc(0, 0);
            return NULL;
        }

        node->data = data;
        node->next = head;
        head = node;

        return data;
    }
    else if (mode == 0)
    {
        free_all(&head);
        head = NULL;
    }
    return NULL;
}
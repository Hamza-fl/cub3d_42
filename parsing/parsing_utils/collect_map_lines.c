/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:10 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:10 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static  bool    append_node(t_line_node **head, char *line)
{
    t_line_node *new_node = malloc(sizeof(t_line_node));
    t_line_node *cur;

    if (!new_node)
        return false;
    new_node->line = line;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = new_node;
    }
    return true;
}


bool collect_map_lines(int fd, char *first_line, char ***out_lines, int *num_lines)
{
    t_line_node *head = NULL;
    t_line_node *cur;
    char        *line = first_line;
    int         count = 0;
    char        **buffer = NULL;
    if (!first_line || !out_lines || !num_lines)
        return false;
    if (!append_node(&head, line))
        return false;
    count++;
    while (true)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (line_is_empty(line)) //check
        {
            free(line);
            break;
        }
        if (!append_node(&head, line))
        {
            cur = head;
            while (cur)
            {
                t_line_node *next = cur->next;
                free(cur->line);
                free(cur);
                cur = next;
            }
            return false;
        }
        count++;
    }
    buffer = malloc(sizeof(char *) * count);
    if (!buffer)
    {
        cur = head;
        while (cur)
        {
            t_line_node *next = cur->next;
            free(cur->line);
            free(cur);
            cur = next;
        }
        return false;
    }
    cur = head;
    int i = 0;
    while (i < count)
    {
        buffer[i] = cur->line;
        t_line_node *next = cur->next;
        free(cur);
        cur = next;
        i++;
    }
    *out_lines = buffer;
    *num_lines = count;
    return true;
}
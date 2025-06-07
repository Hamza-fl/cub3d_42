#include "../includes/parsing.h"

char *ft_strdup(const char *s)
{
    size_t len;
    char   *dup;

    if (!s)
        return NULL;
    len = ft_strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}
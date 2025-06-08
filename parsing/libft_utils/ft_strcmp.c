#include "../includes/parsing.h"

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
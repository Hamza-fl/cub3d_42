#include "../includes/parsing.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    unsigned char uc1;
    unsigned char uc2;

    if (n == 0)
        return 0;

    while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    uc1 = (unsigned char)s1[i];
    uc2 = (unsigned char)s2[i];
    return (int)(uc1 - uc2);
}
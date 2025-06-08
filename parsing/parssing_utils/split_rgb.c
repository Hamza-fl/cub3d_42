#include "../includes/parsing.h"

bool    ft_str_isnumeric(const char *s)
{
    size_t i;

    if (!s || !*s)
        return false;
    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
        i++;
    }
    return true;
}

bool    split_rgb(const char *s, int rgb[3])
{
    char **parts;
    int    count;

    if (!s || !rgb)
        return (false);
    parts = ft_split(s, ',');
    if (!parts)
        return (false);
    count = 0;
    while (parts[count])
        count++;
    if (count != 3)
    {
        print_error("Error\nRGB must have exactly 3 values");
        ft_free_split(parts);
        return (false);
    }
    int i = 0;
    while (i < 3)
    {
        char *trimmed = ft_strtrim(parts[i], " \t\n\r\f\v"); // all spaces
        long val;

        if (!trimmed)
        {
            ft_free_split(parts);
            return (false);
        }
        if (!ft_str_isnumeric(trimmed))
        {
            print_error("Error\nNon‐numeric RGB value\n");
            free(trimmed);
            ft_free_split(parts);
            return (false);
        }
        val = ft_atoi(trimmed);
        free(trimmed);
        if (val < 0 || val > 255)
        {
            print_error("Error\nRGB value out of range (0–255)\n");
            ft_free_split(parts);
            return (false);
        }
        rgb[i] = (int)val;
        i++;
    }
    ft_free_split(parts);
    return (true);
}
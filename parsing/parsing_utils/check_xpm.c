#include "../../includes/cub3d.h"

bool file_has_xpm_extension(const char *path)
{
    size_t len;

    if (!path)
        return false;

    len = ft_strlen(path);
    if (len < 4)
        return false;

    /* Compare the last 4 characters to ".xpm" */
    if (ft_strncmp(path + (len - 4), ".xpm", 4) == 0)
        return true;
    else
        return false;
}
#include "includes/parsing.h"

int main(int argc, char **argv)
{
    t_parsing data;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!ft_parsing(argv[1], &data))
    {
        fprintf(stderr, "Parsing failed.\n");
        return EXIT_FAILURE;
    }

    /* Print texture paths */
    printf("NO texture: %s\n", data.no_texture);
    printf("SO texture: %s\n", data.so_texture);
    printf("WE texture: %s\n", data.we_texture);
    printf("EA texture: %s\n", data.ea_texture);

    /* Print floor and ceiling colors in hex */
    printf("Floor color:   0x%06X\n", data.floor_color);
    printf("Ceiling color: 0x%06X\n", data.ceiling_color);

    /* Print the map */
    printf("\nMap (width=%d, height=%d):\n", data.map_width, data.map_height);
    for (int r = 0; r < data.map_height; ++r)
        printf("%s\n", data.map[r]);

    /* Print player position and direction */
    printf("\nPlayer start:\n");
    printf("  Position: (%.2f, %.2f)\n", data.player_pos.x, data.player_pos.y);
    printf("  Direction: %c\n", data.player_dir);

    return EXIT_SUCCESS;
}

#include "../cub.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **transpose_map(char **original_map, int height, int width)
{
    // Allocate memory for the transposed map
    char **transposed_map = malloc(width * sizeof(char *));
    for (int i = 0; i < width; i++)
        transposed_map[i] = malloc((height + 1) * sizeof(char)); // +1 for '\0'

    // Transpose the map
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((size_t)x < strlen(original_map[y])) // Handle rows with different lengths
                transposed_map[x][y] = original_map[y][x];
            else
                transposed_map[x][y] = ' '; // Fill with a space if necessary
        }
    }

    // Add null terminators to each transposed row
    for (int i = 0; i < width; i++)
        transposed_map[i][height] = '\0';

    return transposed_map;
}


int	main(int ac, char **av)
{
	t_param	*param;

	if (ac == 2)
	{
		param = NULL;
		param = malloc(1 * sizeof(t_param));
		if (!param)
			ft_error("memory allocation for param failed", param);
		init_param(param);
		parse_map_file(param, av);
		if (!set_screen(param))
			ft_error("memory allocation failed", param);
		load_texture(param);
		cast_rays_and_render(param);
		event_handler(param);
		mlx_loop(param->mlx);
		close(param->fd);
		clean_all(param);
		return (0);
	}
	else
		printf("Double-check your arguments\n");
	return (1);
}

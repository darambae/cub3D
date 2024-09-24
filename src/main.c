#include "../cub.h"

/* Pseudo code
	1. parsing the map(.cub file) -> if success, go to step 2. else, print error message "Error\n" and exit the program
	2. initialize the parameters
	3. draw the map
	4. handle the events
	5. close the window (free the allocated memory)

	structure of the program : 3 loops
	 - first loop: mlx-loop
	 - second loop: from x = 0 to x = width
	 - third loop: while (!hit)
	*/

int	main(int ac, char **av)
{
	t_param	*param;

	param = NULL;
	param = malloc(1 * sizeof(t_param));
	if (ac != 2 || !param)
	{
		printf("Error\n");
		return (1);
	}
	init_param(param);
	parse_map_file(param, av);
	int i = 0;
	int j = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j])
		{
			printf("%c", param->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("map_x: %d, map_y: %d\n", param->map_x, param->map_y);
	cast_rays_and_render(param);
	event_handler(param);
	mlx_loop(param->mlx);
	close(param->fd);
	clean_all(param);
	return (0);
}

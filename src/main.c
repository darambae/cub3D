#include "../cub.h"

/* Pseudo code
	1. parsing the map(.cub file) -> if success, go to step 2. else, print error
message "Error\n" and exit the program
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
	if (!set_screen(param))
		ft_error("memory allocation failed", param);
	if (!load_texture(param))
		exit(1);
	cast_rays_and_render(param);
	event_handler(param);
	mlx_loop(param->mlx);
	close(param->fd);
	clean_all(param);
	return (0);
}

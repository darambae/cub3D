#include "../cub.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		swap_x_y(param);
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

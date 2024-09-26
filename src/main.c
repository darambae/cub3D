#include "../cub.h"

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
	load_texture(param);
	cast_rays_and_render(param);
	event_handler(param);
	mlx_loop(param->mlx);
	close(param->fd);
	clean_all(param);
	return (0);
}

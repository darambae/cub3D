#include "../cub.h"

/*int world_map[9][18] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};*/

void	clean_tex(t_texture *tex, t_param *param)
{
	int	i;

	i = 0;
	while (tex[i].path && i < 4)
	{
		free(tex[i].path);
		tex[i].path = NULL;
		mlx_destroy_image(param->mlx, tex[i].img);
		free(tex[i].addr);
		i++;
	}
	free(tex);
	tex = NULL;
}

void	clean_mlx(t_param *param)
{
	if (param->mlx)
	{
		if (param->window)
		{
			mlx_destroy_window(param->mlx, param->window);
			param->window = NULL;
		}
		if (param->img)
		{
			mlx_destroy_image(param->mlx, param->img);
			param->img = NULL;
		}
		if (param->addr)
		{
			free(param->addr);
			param->addr = NULL;
		}
	}
	mlx_destroy_display(param->mlx);
	param->mlx = NULL;
}

void	clean_all(t_param *param)
{
	if (param)
	{
		if (param->mlx)
			clean_mlx(param);
		if (param->format)
		{
			free(param->format);
			param->format = NULL;
		}
		if (param->map)
			clean_map(param->map);
		if (param->tex)
			clean_tex(param->tex, param);
	}
	free(param);
	param = NULL;
}

void	ft_error(char *str, t_param *param)
{
	close(param->fd);
	clean_all(param);
	printf("ERROR: %s\n", str);
	exit (1);
}

int	main(int ac, char **av)
{
	(void)av;
	t_param	*param;
	int y = 0;
	int x = 0;
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
	param = NULL;
	if (ac != 2)
	{
		printf("Error\n");
		return (1);
	}
	param = malloc(1 * sizeof(t_param));
	if (!param)
	{
		printf("Error\n");
		return (1);
	}
	init_param(param);
	if (check_extension(av[1]) < 0)
		ft_error("filename must finish by .cub", param);
	param->fd = check_openable(av[1]);
	if (param->fd < 0)
		ft_error("file is not openable", param);
	check_texture(param);
	if (!param->map)
		ft_error("no map in the file.cub", param);
	if (!load_texture(param))//send error if path are not good
		exit(1);
	cast_rays_and_render(param);
	event_handler(param);
	mlx_loop(param->mlx);
	while (param->map[y])
	{
		while (param->map[y][x])
		{
			write(1, &param->map[y][x], 1);
			x++;
		}
		x = 0;
		y++;
	}
	close(param->fd);
	clean_all(param);
	return (0);
}

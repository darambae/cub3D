#include "../cub.h"

void	init_texture(t_param *param)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		param->tex[i].path = NULL;
		param->tex[i].w = 0;
		param->tex[i].h = 0;
		param->tex[i].img = NULL;
		param->tex[i].addr = NULL;
		param->tex[i].bits_per_pixel = 0;
		param->tex[i].size_line = 0;
		param->tex[i].endian = 0;
		i++;
	}
}

bool	alloc_param(t_param *param)
{
	param->tex = (t_texture *)malloc(sizeof(t_texture) * 4);
	param->format = ft_calloc(6, sizeof(int));
	if (!param->tex || !param->format)
		return (false);
	return (true);
}

bool	set_screen(t_param *param)
{
	param->mlx = mlx_init();
	param->window = mlx_new_window(param->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	param->img = mlx_new_image(param->mlx, SCREEN_W, SCREEN_H);
	param->addr = mlx_get_data_addr(param->img, &param->bits_per_pixel, \
		&param->size_line, &param->endian);
	if (param->mlx == NULL || param->window == NULL || param->img == NULL \
		|| param->addr == NULL)
		return (false);
	return (true);
}

void	init_param(t_param *param)
{
	param->fd = 0;
	param->map = NULL;
	param->map_y = 0;
	param->map_x = 0;
	if (!alloc_param(param) || !set_screen(param))
	{
		printf("memory allocation failed");
		clean_all(param);
		exit(1);
	}
	init_texture(param);
	param->ray.draw_start = 0;
	param->ray.draw_end = 0;
	param->fov = 0.66;
	param->dir.x = 1;
	param->dir.y = 0;
	param->plane.x = 0;
	param->plane.y = param->fov;
	param->mini.scale = 10;
	param->mini.color = create_rgb(250, 240, 230);
	param->pos.x = -1;
	param->pos.y = -1;
	param->color_floor = 0;
	param->color_ceiling = 0;
}

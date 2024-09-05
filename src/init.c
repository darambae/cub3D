#include "../cub.h"

//in parsing
bool	load_texture(t_param *param)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		param->tex[i].img = mlx_xpm_file_to_image(param->mlx, \
			param->tex[i].path, &param->tex[i].w, &param->tex[i].h);
		if (!param->tex[i].img)
		{
			printf("Error: Unable to load t from %s\n", param->tex[i].path);
			return (false);
		}
		param->tex[i].addr = mlx_get_data_addr(param->tex[i].img, \
			&param->tex[i].bits_per_pixel, &param->tex[i].size_line, &param->tex[i].endian);
		i++;
	}
	return (true);
}


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
	param->pos = (t_vec *)malloc(sizeof(t_vec));
	param->dir = (t_vec *)malloc(sizeof(t_vec));
	param->plane = (t_vec *)malloc(sizeof(t_vec));
	param->tex = (t_texture *)malloc(sizeof(t_texture) * 4);

	if (param->pos == NULL || param->dir == NULL || param->plane == NULL \
		|| param->tex == NULL)
	{
		printf("Error\n");
		return (false);
	}
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
	{
		printf("Error\n");
		return (false);
	}
	return (true);
}

void	init_param(t_param *param)
{
	param->map_w = 9;
	param->map_l = 19;
	//set default texture path temporarily
	if (!alloc_param(param) || !set_screen(param))
		exit(1);
	init_texture(param);
	for (int i = 0; i < 4; i++)
		param->tex[i].path = "./assets/mountain_2_.xpm";
	if (!load_texture(param))
		exit(1);
	param->draw_start = 0;
	param->draw_end = 0;
	param->fov = 0.66;
	param->dir->x = -1;
	param->dir->y = 0;
	param->plane->x = 0;
	param->plane->y = param->fov;
	//parsing part
	param->pos->x = 6;
	param->pos->y = 5;
	param->color_floor = create_rgb(200, 200, 150);
	param->color_ceiling = create_rgb(60, 205, 200);
}

#include "../cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_param(t_param *param)
{
	param->map_w = 9;
	param->map_l = 19;
	param->draw_start = 0;
	param->draw_end = 0;
	param->fov = 0.66;
	param->mlx = mlx_init();
	param->window = mlx_new_window(param->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	param->img = mlx_new_image(param->mlx, SCREEN_W, SCREEN_H);
	param->addr = mlx_get_data_addr(param->img, &param->bits_per_pixel, &param->size_line, &param->endian);
	if (param->mlx == NULL || param->window == NULL || param->img == NULL || param->addr == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	param->map = (t_map **)malloc(sizeof(t_map *) * param->map_w);
	for (int i = 0; i < param->map_w; i++)
		param->map[i] = (t_map *)malloc(sizeof(t_map) * param->map_l);
	param->pos = (t_map *)malloc(sizeof(t_map));
	param->dir = (t_map *)malloc(sizeof(t_map));
	param->plane = (t_map *)malloc(sizeof(t_map));
	if (param->map == NULL || param->pos == NULL || param->dir == NULL || param->plane == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	param->pos->x = 6;
	param->pos->y = 5;
	param->dir->x = -1;
	param->dir->y = 0;
	param->plane->x = 0;
	param->plane->y = param->fov;
	param->color_floor = create_rgb(200, 200, 150);
	param->color_ceiling = create_rgb(60, 205, 200);
	param->texture_y = "../assets/mountain_square.xmp";
	param->texture_x = "../assets/mountain_square.xmp";
}
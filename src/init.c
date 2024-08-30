#include "../cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_param(t_param *param)
{
	param->mlx = mlx_init();
	param->window = mlx_new_window(param->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	param->map = (t_map **)malloc(sizeof(t_map *) * param->map_width);
	param->pos = (t_map *)malloc(sizeof(t_map));
	param->dir = (t_map *)malloc(sizeof(t_map));
	param->plane = (t_map *)malloc(sizeof(t_map));
	param->pos->x = 4;
	param->pos->y = 8;
	param->dir->x = -1;
	param->dir->y = 0;
	param->plane->x = 0;
	param->plane->y = 0.66;
	param->color_floor = create_rgb(200, 200, 150);
	param->color_ceiling = create_rgb(60, 205, 200);
}
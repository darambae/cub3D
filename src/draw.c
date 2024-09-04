#include "../cub.h"

void	my_mlxx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * SCREEN_W + x) * (param->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	verline(t_param *param, int x, int color)
{
	double	y;

	y = 0;
	while (y < param->draw_start)
	{
		my_mlxx_pixel_put(param, x, y, param->color_ceiling);
		y += 0.1;
	}
	while (y < param->draw_end)
	{
		my_mlxx_pixel_put(param, x, y, color);
		y += 0.1;
	}
	while (y < SCREEN_H)
	{
		my_mlxx_pixel_put(param, x, y, param->color_floor);
		y += 0.1;
	}
}


void	draw_line(t_param *param)
{
	int			cur;
	double		camera_x;
	t_map		ray_dir;
	t_map		map;
	t_map		delat_dist;
	t_map		side_dist;
	t_map		step;
	int			color;
	int			hit;
	int			side;
	int			line_height;
	double		perpWall_dist;

	cur = 0;
	while (cur < SCREEN_W)
	{
		camera_x = 2 * cur / (double)SCREEN_W;
		ray_dir = addVectors(*param->dir, scaleVectors(*param->plane, camera_x));
		map = (t_map){(int)param->pos->x, (int)param->pos->y};
		delat_dist = (t_map){fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};
		hit = 0;
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (param->pos->x - map.x) * delat_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - param->pos->x) * delat_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (param->pos->y - map.y) * delat_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - param->pos->y) * delat_dist.y;
		}
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delat_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delat_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (world_map[(int)map.x][(int)map.y] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWall_dist = (map.x - param->pos->x + (1 - step.x) / 2) / ray_dir.x;
		else
			perpWall_dist = (map.y - param->pos->y + (1 - step.y) / 2) / ray_dir.y;
		line_height = (int)(SCREEN_H / perpWall_dist);
		param->draw_start = -line_height / 2 + SCREEN_H / 2;
		if (param->draw_start < 0)
			param->draw_start = 0;
		param->draw_end = line_height / 2 + SCREEN_H / 2;
		if (param->draw_end >= SCREEN_H)
			param->draw_end = SCREEN_H - 1;
		if (side == 1)
			color = param->pattern_y;
		else
			color = param->pattern_x;
		verline(param, cur, color);
		cur++;
	}
	mlx_put_image_to_window(param->mlx, param->window, param->img, 0, 0);
}

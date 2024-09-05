#include "../cub.h"

void	my_mlxx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * SCREEN_W + x) * (param->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

int	print_wall(t_param *param, int y, int tex_num, double wall_x)
{
	int		color;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		tex_w;
	int		tex_h;

	tex_w = param->tex[tex_num].w;
	tex_h = param->tex[tex_num].h;
	tex_x = (int)(wall_x * (double)tex_w);
	if ((param->side == 0 && param->ray_dir.x > 0) || (param->side == 1 && param->ray_dir.y < 0))
		tex_x = tex_w - tex_x - 1;
	step = 1.0 * tex_h / (param->draw_end - param->draw_start);
	tex_pos = (y - param->draw_start) * step;
	tex_y = (int)tex_pos & (tex_h - 1);
	color = *(unsigned int *)(param->tex[tex_num].addr + (tex_y * tex_w + tex_x) * (param->tex[tex_num].bits_per_pixel / 8));
	return (color);
}

void	verline(t_param *param, int x, int tex_num, double wall_x)
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
		my_mlxx_pixel_put(param, x, y, print_wall(param, y, tex_num, wall_x));
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
	t_vec		map;
	t_vec		delta_dist;
	t_vec		side_dist;
	t_vec		step;
	int			tex_num;
	int			hit;
	int			line_height;
	double		perpWall_dist;
	double		wall_x;

	cur = 0;
	while (cur < SCREEN_W)
	{
		camera_x = 2 * cur / (double)SCREEN_W - 1;
		param->ray_dir = addVectors(*param->dir, scaleVectors(*param->plane, camera_x));
		map = (t_vec){(int)param->pos->x, (int)param->pos->y};
		delta_dist = (t_vec){fabs(1 / param->ray_dir.x), fabs(1 / param->ray_dir.y)};
		hit = 0;
		if (param->ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (param->pos->x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - param->pos->x) * delta_dist.x;
		}
		if (param->ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (param->pos->y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - param->pos->y) * delta_dist.y;
		}
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				param->side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				param->side = 1;
			}
			if (world_map[(int)map.x][(int)map.y] > 0)
				hit = 1;
		}
		if (param->side == 0)
			perpWall_dist = (map.x - param->pos->x + (1 - step.x) / 2) / param->ray_dir.x;
		else
			perpWall_dist = (map.y - param->pos->y + (1 - step.y) / 2) / param->ray_dir.y;
		line_height = (int)(SCREEN_H / perpWall_dist);
		
		param->draw_start = -line_height / 2 + SCREEN_H / 2;
		if (param->draw_start < 0)
			param->draw_start = 0;
		param->draw_end = line_height / 2 + SCREEN_H / 2;
		if (param->draw_end >= SCREEN_H)
			param->draw_end = SCREEN_H - 1;
		if (param->side == 0)
			wall_x = param->pos->y + perpWall_dist * param->ray_dir.y;
		else
			wall_x = param->pos->x + perpWall_dist * param->ray_dir.x;
		wall_x -= floor(wall_x);
		if (param->side == 1 && param->ray_dir.y > 0)
			tex_num = 0;
		else if (param->side == 1 && param->ray_dir.y < 0)
			tex_num = 1;
		else if (param->side == 0 && param->ray_dir.x > 0)
			tex_num = 2;
		else
			tex_num = 3;
		verline(param, cur, tex_num, wall_x);
		cur++;
	}
	mlx_put_image_to_window(param->mlx, param->window, param->img, 0, 0);
}

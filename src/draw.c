#include "../cub.h"

int	get_text_pix(t_ray r, int y, t_texture t, double wall_x)
{
	int		color;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;

	tex_x = (int)(wall_x * (double)t.w);
	if ((r.side == 0 && r.dir.x > 0) || (r.side == 1 && r.dir.y < 0))
		tex_x = t.w - tex_x - 1;
	step = 1.0 * t.h / (r.draw_end - r.draw_start);
	tex_pos = (y - r.draw_start) * step;
	tex_y = (int)(tex_pos) % t.h;
	color = *(unsigned int *)(t.addr + (tex_y * t.w + tex_x) * \
		(t.bits_per_pixel / 8));
	return (color);
}

//0 = north, 1 = east, 2 = south, 3 = west
t_texture	get_wall_dir(t_param *param)
{
	int	tex_num;

	if (param->ray.side == 0)
	{
		if (param->ray.dir.x > 0)
			tex_num = 1;
		else
			tex_num = 3;
	}
	else
	{
		if (param->ray.dir.y > 0)
			tex_num = 2;
		else
			tex_num = 0;
	}
	return (param->tex[tex_num]);
}

void	verline(t_param *param, int x, t_texture t, double wall_x)
{
	double	y;

	y = 0;
	while (y < param->ray.draw_start)
	{
		my_mlxx_pixel_put(param, x, y, param->color_ceiling);
		y++;
	}
	while (y < param->ray.draw_end)
	{
		my_mlxx_pixel_put(param, x, y, get_text_pix(param->ray, y, t, wall_x));
		y++;
	}
	while (y < SCREEN_H)
	{
		my_mlxx_pixel_put(param, x, y, param->color_floor);
		y++;
	}
}

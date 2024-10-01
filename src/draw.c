#include "../cub.h"

int	get_text_pix(t_ray r, int y, t_texture t)
{
	int		color;

	t.tex_x = (int)(t.wall_x * (double)t.w);
	if ((r.side == 0 && r.dir.x > 0) || (r.side == 1 && r.dir.y < 0))
		t.tex_x = t.w - t.tex_x - 1;
	t.step = 1.0 * t.h / r.line_height;
	t.tex_pos = (y - r.draw_start) * t.step;
	t.tex_y = (int)(t.tex_pos) % t.h;
	if (t.tex_y < 0)
		t.tex_y += t.h;
	color = *(unsigned int *)(t.addr + (t.tex_y * t.w + t.tex_x) * \
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
			tex_num = 2;
		else
			tex_num = 0;
	}
	else
	{
		if (param->ray.dir.y > 0)
			tex_num = 1;
		else
			tex_num = 3;
	}
	return (param->tex[tex_num]);
}

void	print_direction(t_param *param)
{
	mlx_string_put(param->mlx, param->window, 10, param->map_x \
		* param->mini.scale, create_rgb(0, 0, 0), "N");
	mlx_string_put(param->mlx, param->window, param->map_x \
		* param->mini.scale / 2, 20, create_rgb(0, 0, 0), "W");
	mlx_string_put(param->mlx, param->window, param->map_x \
		* param->mini.scale / 2, param->map_y * param->mini.scale + 10, \
		create_rgb(0, 0, 0), "S");
	mlx_string_put(param->mlx, param->window, param->map_x \
		* param->mini.scale, param->map_x * param->mini.scale, \
		create_rgb(0, 0, 0), "E");
}

void	verline(t_param *param, int x, t_texture t)
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
		my_mlxx_pixel_put(param, x, y, get_text_pix(param->ray, y, t));
		y++;
	}
	while (y < SCREEN_H)
	{
		my_mlxx_pixel_put(param, x, y, param->color_floor);
		y++;
	}
}

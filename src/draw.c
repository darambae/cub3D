#include "../cub.h"
int	get_text_pix(t_param *param, int y, t_texture t, double wall_x)
{
	int		color;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;

	// Calculate the x-coordinate of the texture based on the wall hit position
	tex_x = (int)(wall_x * (double)t.w);

	// Reverse texture horizontally based on the ray's direction and side hit
	if ((param->ray.side == 0 && param->ray.dir.x > 0) || 
		(param->ray.side == 1 && param->ray.dir.y < 0))
		tex_x = t.w - tex_x - 1;

	// Step defines how much we move on the texture per pixel drawn vertically
	step = 1.0 * t.h / (param->ray.draw_end - param->ray.draw_start);

	// Calculate the texture's y position at the current y value of the wall
	tex_pos = (y - param->ray.draw_start) * step;
	tex_y = (int)(tex_pos) % t.h;

	// Retrieve the color from the texture based on the calculated tex_x and tex_y
	color = *(unsigned int *)(t.addr + (tex_y * t.w + tex_x) * (t.bits_per_pixel / 8));

	return (color);
}



// int	get_text_pix(t_param *param, int y, t_texture t, double wall_x)
// {
// 	int		color;
// 	int		tex_x;
// 	int		tex_y;
// 	double	tex_pos;
// 	double	step;

// 	tex_x = (int)(wall_x * (double)t.w);
// 	if ((param->ray.side == 0 && param->ray.dir.x > 0) 
// 		|| (param->ray.side == 1 && param->ray.dir.y < 0))
// 		tex_x = t.w - tex_x - 1;
// 	step = 1.0 * t.h / (param->ray.draw_end - param->ray.draw_start + 1);
// 	tex_pos = (y - param->ray.draw_start) * step;
// 	tex_y = (int)(tex_pos) % t.h;
// 	if (tex_y < 0)
// 		tex_y = 0;
// 	if (tex_y >= t.h)
// 		tex_y = t.h - 1;
// 	color = *(unsigned int *)(t.addr + (tex_y * t.w + tex_x) * 
// 		(t.bits_per_pixel / 8));
// 	return (color);
// }

t_texture	get_wall_dir(t_param *param)
{
	int	tex_num;

	if (param->ray.side == 0)
	{
		if (param->ray.dir.x > 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (param->ray.dir.y > 0)
			tex_num = 2;
		else
			tex_num = 3;
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
		my_mlxx_pixel_put(param, x, y, get_text_pix(param, y, t, wall_x));
		y++;
	}
	while (y < SCREEN_H)
	{
		my_mlxx_pixel_put(param, x, y, param->color_floor);
		y++;
	}
}

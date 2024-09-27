#include "../cub.h"

void	print_square(t_param *param, int x, int y)
{
	int		i;
	int		j;
	int		screen_x;
	int		screen_y;

	i = 0;
	while (i < param->mini.scale)
	{
		j = 0;
		while (j < param->mini.scale)
		{
			screen_x = x * param->mini.scale + i;
			screen_y = y * param->mini.scale + j;
			my_mlxx_pixel_put(param, screen_x, screen_y, param->mini.color);
			j++;
		}
		i++;
	}
}

void	print_wall(t_param *param)
{
	int		i;
	int		j;

	i = 0;
	while (i < param->map_x)
	{
		j = 0;
		while (j < (int)ft_strlen(param->map[i]))
		{
			if (param->map[i][j] == '1')
				print_square(param, i, j);
			j++;
		}
		i++;
	}
}

void	print_ray_on_minimap(t_param *p)
{
	t_ray	ray;
	int		cur;
	double	ray_length;

	cur = -1;
	while (++cur < 50)
	{
		ray.camera_x = (2 * cur / 50.0) - 1;
		ray.dir = add_vec(p->dir, scale_vec(p->plane, ray.camera_x * p->fov));
		ray.map = scale_vec(p->pos, p->mini.scale);
		ray_length = 0;
		while (ray_length < 2.0)
		{
			ray.map = add_vec(p->pos, scale_vec(ray.dir, ray_length));
			ray.map = scale_vec(ray.map, p->mini.scale);
			if (ray.map.x < 0 || ray.map.y < 0 || ray.map.x >= p->map_x * \
				p->mini.scale || ray.map.y >= p->map_y * p->mini.scale \
				|| p->map[(int)(ray.map.x / p->mini.scale)] \
				[(int)(ray.map.y / p->mini.scale)] == '1')
				break ;
			my_mlxx_pixel_put(p, ray.map.x, ray.map.y,
				create_rgb(255, 255, 0));
			ray_length += 0.1;
		}
	}
}

void	print_player(t_param *param)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = param->pos.x * param->mini.scale;
	player_y = param->pos.y * param->mini.scale;
	i = -2;
	while (i++ < 2)
	{
		j = -2;
		while (j++ < 2)
			my_mlxx_pixel_put(param, player_x + i, player_y + j, \
				create_rgb(255, 0, 0));
	}
}

void	print_minimap(t_param *param)
{
	print_ray_on_minimap(param);
	print_player(param);
	print_wall(param);
}

#include "../cub.h"

void	init_minimap(t_param *param)
{
	param->mini.scale = 10;
	param->mini.color = create_rgb(250, 240, 230);
}

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
	while (i < param->map_w)
	{
		j = 0;
		while (j < param->map_l)
		{
			if (world_map[i][j] == 1)
				print_square(param, i, j);
			j++;
		}
		i++;
	}
}

void	print_ray_on_minimap(t_param *param)
{
	t_ray	ray;
	int		cur;
	int		max_rays;
	double	ray_length = 0;

	max_rays = 50; // Define number of rays here
    for (cur = 0; cur < max_rays; cur++)
    {
        // Adjust the camera_x based on current ray and FOV
        ray.camera_x = 2 * cur / (double)max_rays - 1;
		// Calculate the direction of the ray based on camera_x and fov
		ray.dir = add_vec(param->dir, scale_vec(param->plane, ray.camera_x * param->fov));
		// Start at player's position and extend ray outward
		ray.map = scale_vec(param->pos, param->mini.scale);
        
        // Extend the ray outward by a certain length (range)
        while (ray_length < 3.0) // Define max ray length here
        {
			ray.map = add_vec(param->pos, scale_vec(ray.dir, ray_length));
			ray.map = scale_vec(ray.map, param->mini.scale);
            // Draw the ray on the minimap as a line
			if (world_map[(int)ray.map.x][(int)ray.map.y] == 1)
				break;
			my_mlxx_pixel_put(param, ray.map.x, ray.map.y, create_rgb(255, 255, 0)); // Yellow for the ray
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
	init_minimap(param);
	print_wall(param);
	print_player(param);
	print_ray_on_minimap(param);
}

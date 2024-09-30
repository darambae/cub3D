#include "../cub.h"

t_texture	calcul_wall_dist_hei(t_param *param)
{
	t_ray		*r;
	t_texture	t;

	r = &param->ray;
	t = get_wall_dir(param);
	get_perp_wall_dist(param);
	r->line_height = (int)(SCREEN_H / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_H / 2;
	r->draw_end = r->line_height / 2 + SCREEN_H / 2;
	if (r->draw_end >= SCREEN_H)
		r->draw_end = SCREEN_H - 1;
	if (r->side == 0)
		t.wall_x = param->pos.y + r->perp_wall_dist * r->dir.y;
	else
		t.wall_x = param->pos.x + r->perp_wall_dist * r->dir.x;
	t.wall_x -= floor(t.wall_x);
	return (t);
}

void	calcul_step_side_dist(t_param *param)
{
	t_ray	*ray;

	ray = &param->ray;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (param->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - param->pos.x) * \
			ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (param->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - param->pos.y) * \
			ray->delta_dist.y;
	}
}

void	dda(t_param *param)
{
	int		hit;
	t_ray	*ray;

	ray = &param->ray;
	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (param->map[(int)ray->map.x][(int)ray->map.y] != '0')
			hit = 1;
	}
}

void	setup_ray(t_param *param, int cur)
{
	t_ray	*ray;

	ray = &param->ray;
	ray->camera_x = 2 * cur / (double)SCREEN_W - 1;
	ray->map = (t_vec){(int)param->pos.x, (int)param->pos.y};
	ray->dir = add_vec(param->dir, scale_vec(param->plane, ray->camera_x));
	if (ray->dir.y == 0)
	{
		ray->delta_dist.x = 1;
		ray->delta_dist.y = fabs(1 / ray->dir.x);
	}
	else if (ray->dir.x == 0)
	{
		ray->delta_dist.x = fabs(1 / ray->dir.y);
		ray->delta_dist.y = 1;
	}
	else
		ray->delta_dist = (t_vec){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	calcul_step_side_dist(param);
}

void	cast_rays_and_render(t_param *param)
{
	int	cur;

	cur = SCREEN_W - 1;  // Start from the rightmost column (East)
	while (cur >= 0)     // Render to the leftmost column (West)
	{
		setup_ray(param, cur);
		dda(param);
		verline(param, cur, calcul_wall_dist_hei(param));
		cur--;  // Decrement to move from East to West
	}
	print_minimap(param);
	mlx_put_image_to_window(param->mlx, param->window, param->img, 0, 0);
}


// void	cast_rays_and_render(t_param *param)
// {
// 	int	cur;

// 	cur = 0;
// 	while (cur < SCREEN_W)
// 	{
// 		setup_ray(param, cur);
// 		dda(param);
// 		verline(param, cur, calcul_wall_dist_hei(param));
// 		cur++;
// 	}
// 	print_minimap(param);
// 	mlx_put_image_to_window(param->mlx, param->window, param->img, 0, 0);
// }

#include "../cub.h"

void	get_perp_wall_dist(t_param *param)
{
	double	min_dist;
	t_ray	*r;

	r = &param->ray;
	min_dist = 1;
	printf("dir.x: %f, dir.y: %f, map.x: %f, map.y: %f\n", r->dir.x, r->dir.y, r->map.x, r->map.y);
	if (r->side == 0)
		r->perp_wall_dist = (r->map.x - param->pos.x + \
			(1 - r->step.x) / 2) / r->dir.x;
	else
		r->perp_wall_dist = (r->map.y - param->pos.y + \
			(1 - r->step.y) / 2) / r->dir.y;
	// if (r->perp_wall_dist < 0.1)
	// 	r->perp_wall_dist = 0.1;
	if (r->perp_wall_dist < min_dist)
		r->perp_wall_dist = min_dist;
	printf("perp_wall_dist: %f\n", r->perp_wall_dist);
}

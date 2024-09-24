#include "../cub.h"

void	get_perp_wall_dist(t_param *param)
{
	double	min_dist;
	t_ray	*r;

	r = &param->ray;
	min_dist = 1;
	//printf("r.side: %d, dir.x: %f, dir.y: %f, map.x: %f, map.y: %f\n", r->side, r->dir.x, r->dir.y, param->pos.x, param->pos.y);
	// if (fabs(r->dir.x) < 1e-6)
	// 	r->dir.x = (r->dir.x < 0) ? -1e-6 : 1e-6;
	// if (fabs(r->dir.y) < 1e-6)
	// 	r->dir.y = (r->dir.y < 0) ? -1e-6 : 1e-6;
	printf("r->map.x: %f, r->map.y: %f\n", r->map.x, r->map.y);
	printf("param->pos.x: %f, param->pos.y: %f\n", param->pos.x, param->pos.y);
	printf("r->dir.x: %f, r->dir.y: %f\n", r->dir.x, r->dir.y);
	if (r->side == 0)
		r->perp_wall_dist = (r->map.x - param->pos.x + \
			(1 - r->step.x) / 2) / r->dir.x;
	else
		r->perp_wall_dist = (r->map.y - param->pos.y + \
			(1 - r->step.y) / 2) / r->dir.y;
	if (r->perp_wall_dist < min_dist)
		r->perp_wall_dist = min_dist;
	//printf("perp_wall_dist: %f\n", r->perp_wall_dist);
}

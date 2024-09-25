#include "../cub.h"

void	get_perp_wall_dist(t_param *param)
{
	double	min_dist;
	t_ray	*r;

	r = &param->ray;
	min_dist = 1;
	if (r->side == 0)
		r->perp_wall_dist = (r->map.x - param->pos.x + \
			(1 - r->step.x) / 2) / r->dir.x;
	else
		r->perp_wall_dist = (r->map.y - param->pos.y + \
			(1 - r->step.y) / 2) / r->dir.y;
	if (r->perp_wall_dist < min_dist)
		r->perp_wall_dist = min_dist;
}

double normalize_angle(double angle) 
{
    angle = fmod(angle, 2 * PI); // Get remainder of angle divided by 2π
    if (angle < 0)
        angle += 2 * PI; // Adjust negative angles
    return angle;
}


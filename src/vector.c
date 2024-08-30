
#include "../cub.h"

t_vector	addVectors(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vector	subVectors(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_vector	scaleVectors(t_vector a, double n)
{
	t_vector	res;

	res.x = a.x * n;
	res.y = a.y * n;
	return (res);
}


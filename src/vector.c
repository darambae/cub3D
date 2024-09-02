
#include "../cub.h"

t_map	addVectors(t_map a, t_map b)
{
	t_map	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_map	subVectors(t_map a, t_map b)
{
	t_map	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_map	scaleVectors(t_map a, double n)
{
	t_map	res;

	res.x = a.x * n;
	res.y = a.y * n;
	return (res);
}



#include "../cub.h"

t_vec	addVectors(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vec	subVectors(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_vec	scaleVectors(t_vec a, double n)
{
	t_vec	res;

	res.x = a.x * n;
	res.y = a.y * n;
	return (res);
}


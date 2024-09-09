
#include "../cub.h"

t_vec	add_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vec	sub_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_vec	scale_vec(t_vec a, double n)
{
	t_vec	res;

	res.x = a.x * n;
	res.y = a.y * n;
	return (res);
}

t_vec	divide_vec(t_vec a, double n)
{
	t_vec	res;

	res.x = a.x / n;
	res.y = a.y / n;
	return (res);
}

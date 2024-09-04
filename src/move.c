#include "../cub.h"

void	rotate(t_param *param, double angle)
{
	double	old_dir;
	double	old_plane;

	old_dir = param->dir->x;
	old_plane = param->plane->x;

	param->dir->x = param->dir->x * cos(angle) - param->dir->y * sin(angle);
	param->dir->y = old_dir * sin(angle) + param->dir->y * cos(angle);

	param->plane->x = param->plane->x * cos(angle) - param->plane->y * sin(angle);
	param->plane->y = old_plane * sin(angle) + param->plane->y * cos(angle);
}

int	move_back_forward(t_param *param, bool forward)
{
	double	move_speed;

	move_speed = 0.1;
	if (forward)
	{
		if (world_map[(int)(param->pos->x + param->dir->x * move_speed)][(int)param->pos->y] == 0)
			param->pos->x += param->dir->x * move_speed;
		if (world_map[(int)param->pos->x][(int)(param->pos->y + param->dir->y * move_speed)] == 0)
			param->pos->y += param->dir->y * move_speed;
	}
	else
	{
		if (world_map[(int)(param->pos->x - param->dir->x * move_speed)][(int)param->pos->y] == 0)
			param->pos->x -= param->dir->x * move_speed;
		if (world_map[(int)param->pos->x][(int)(param->pos->y - param->dir->y * move_speed)] == 0)
			param->pos->y -= param->dir->y * move_speed;
	}
	return (0);
}

int	move_left_right(t_param *param, bool right)
{
	double	move_speed;

	move_speed = 0.1;
	if (right)
	{
		if (world_map[(int)(param->pos->x + param->plane->x * move_speed)][(int)param->pos->y] == 0)
			param->pos->x += param->plane->x * move_speed;
		if (world_map[(int)param->pos->x][(int)(param->pos->y + param->plane->y * move_speed)] == 0)
			param->pos->y += param->plane->y * move_speed;
	}
	else
	{
		if (world_map[(int)(param->pos->x - param->plane->x * move_speed)][(int)param->pos->y] == 0)
			param->pos->x -= param->plane->x * move_speed;
		if (world_map[(int)param->pos->x][(int)(param->pos->y - param->plane->y * move_speed)] == 0)
			param->pos->y -= param->plane->y * move_speed;
	}
	return (0);
}

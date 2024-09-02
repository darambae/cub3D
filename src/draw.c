#include "../cub.h"

void	verLine(int x, int drawStart, int drawEnd, t_param *param)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		mlx_pixel_put(param->mlx, param->window, x, y, param->color_ceiling);
		y++;
	}
	while (y < drawEnd)
	{
		mlx_pixel_put(param->mlx, param->window, x, y, create_rgb(255, 255, 255));
		y++;
	}
	while (y < SCREEN_H)
	{
		mlx_pixel_put(param->mlx, param->window, x, y, param->color_floor);
		y++;
	}
}

void	draw_line(t_param param)
{
	int			cur;
	double		cameraX;
	t_map		rayDir;
	t_map		map;
	t_map		delatDist;
	t_map		sideDist;
	t_map		step;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	double		perpWallDist;

	cur = 0;
	while (cur < SCREEN_W)
	{
		cameraX = 2 * cur / (double)SCREEN_W;
		rayDir = addVectors(*param.dir, scaleVectors(*param.plane, cameraX));
		map = (t_map){(int)param.pos->x, (int)param.pos->y, 0};
		delatDist = (t_map){fabs(1 / rayDir.x), fabs(1 / rayDir.y), 0};
		hit = 0;
		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (param.pos->x - map.x) * delatDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - param.pos->x) * delatDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (param.pos->y - map.y) * delatDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - param.pos->y) * delatDist.y;
		}
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += delatDist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += delatDist.y;
				map.y += step.y;
				side = 1;
			}
			if (worldMap[(int)map.x][(int)map.y] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (map.x - param.pos->x + (1 - step.x) / 2) / rayDir.x;
		else
			perpWallDist = (map.y - param.pos->y + (1 - step.y) / 2) / rayDir.y;
		lineHeight = (int)(SCREEN_H / perpWallDist);
		drawStart = -lineHeight / 2 + SCREEN_H / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SCREEN_H / 2;
		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;
		// if (side == 1)
		// 	color = param.color_ceiling;
		// else
		// 	color = param.color_floor;
		verLine(cur, drawStart, drawEnd, &param);
		cur++;
	}
}

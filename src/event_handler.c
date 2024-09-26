#include "../cub.h"

int	close_window(t_param *param)
{
	clean_all(param);
	exit(0);
}

int	key_press(int keycode, t_param *param)
{
	if (keycode == FORWARD)
		move_back_forward(param, true);
	else if (keycode == BACK)
		move_back_forward(param, false);
	else if (keycode == RIGHT)
		move_left_right(param, true);
	else if (keycode == LEFT)
		move_left_right(param, false);
	else if (keycode == ESC)
		close_window(param);
	else if (keycode == LOOK_RIGHT)
		rotate(param, 0.1);
	else if (keycode == LOOK_LEFT)
		rotate(param, -0.1);
	return (0);
}

int	rerendering(int keycode, t_param *param)
{
	ft_bzero(param->addr, SCREEN_W * SCREEN_H * sizeof(int));
	key_press(keycode, param);
	cast_rays_and_render(param);
	return (0);
}

void	event_handler(t_param *param)
{
	mlx_hook(param->window, 2, 1L << 0, rerendering, param);
	mlx_hook(param->window, 17, 0, close_window, param);
}

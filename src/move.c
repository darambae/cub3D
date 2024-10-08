/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:25:19 by dabae             #+#    #+#             */
/*   Updated: 2024/10/01 14:25:20 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// Function to check if a position is walkable (i.e., not a wall)
int	is_valid_position(double x, double y, t_param *param)
{
	return (param->map[(int)x][(int)y] == '0');
}

// Function to handle forward and backward movement
void	move_back_forward(t_param *p, bool forward)
{
	double	sp;
	t_vec	new_pos;

	sp = 0.05;
	if (forward)
		new_pos = add_vec(p->pos, scale_vec(p->dir, sp));
	else if (!forward)
		new_pos = sub_vec(p->pos, scale_vec(p->dir, sp));
	if (is_valid_position(new_pos.x, p->pos.y, p)
		&& is_valid_position(p->pos.x, new_pos.y, p))
		p->pos = new_pos;
}

// Function to handle left and right movement
void	move_left_right(t_param *p, bool right)
{
	double	sp;
	t_vec	new_pos;

	sp = 0.05;
	if (right)
		new_pos = add_vec(p->pos, scale_vec(p->plane, sp));
	else if (!right)
		new_pos = sub_vec(p->pos, scale_vec(p->plane, sp));
	if (is_valid_position(new_pos.x, p->pos.y, p)
		&& is_valid_position(p->pos.x, new_pos.y, p))
		p->pos = new_pos;
}

void	rotate(t_param *param, double ang)
{
	double	old_dir;
	double	old_plane;

	old_dir = param->dir.x;
	old_plane = param->plane.x;
	param->dir.x = param->dir.x * cos(ang) - param->dir.y * sin(ang);
	param->dir.y = old_dir * sin(ang) + param->dir.y * cos(ang);
	param->plane.x = param->plane.x * cos(ang) - param->plane.y * sin(ang);
	param->plane.y = old_plane * sin(ang) + param->plane.y * cos(ang);
}

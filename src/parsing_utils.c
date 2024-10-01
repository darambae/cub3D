/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:25:23 by dabae             #+#    #+#             */
/*   Updated: 2024/10/01 14:25:24 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	swap_x_y(t_param *param)
{
	int	tmp;

	transpose_map(param);
	tmp = param->map_x;
	param->map_x = param->map_y;
	param->map_y = tmp;
	tmp = param->pos.x;
	param->pos.x = param->pos.y;
	param->pos.y = tmp;
}

int	skip_space(char *line, int *i)
{
	if (!ft_strchr(" \t\n\v\r", line[*i]))
		return (-1);
	while (ft_strchr(" \t\n\v\r", line[*i]))
		(*i)++;
	if (!line[*i])
		return (-1);
	return (0);
}

int	get_color_num(int *n, char *line, int *i)
{
	*n = 0;
	if (line[*i] == ',')
		(*i)++;
	if (ft_isdigit(line[*i]))
	{
		*n = ft_atoi(line + *i);
		if (*n < 0 || *n > 255)
			return (-1);
		while (ft_isdigit(line[*i]))
			(*i)++;
		return (0);
	}
	return (-1);
}

void	set_direction(t_param *param, char c)
{
	if (c == 'S')
		param->dir.y++;
	else if (c == 'N')
		param->dir.y--;
	else if (c == 'E')
		param->dir.x++;
	else if (c == 'W')
		param->dir.x--;
	if (param->dir.y > 0)
		param->plane.x = param->fov * -1;
	else if (param->dir.y < 0)
		param->plane.x = param->fov;
	else if (param->dir.x > 0)
		param->plane.y = param->fov;
	else if (param->dir.x < 0)
		param->plane.y = param->fov * -1;
}

// /*copy temp in map and add line at the end*/
void	copy_map(t_param *param, char **temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			param->map[i] = temp[i];
			i++;
		}
	}
	param->map[i++] = param->current_line;
	param->map[i] = '\0';
	if (temp)
		free(temp);
	temp = NULL;
}

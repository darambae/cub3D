/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:25:05 by dabae             #+#    #+#             */
/*   Updated: 2024/10/01 14:25:06 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_char(int *i, t_param *param)
{
	while (param->current_line[*i] && ft_strchr("01NSEW ", \
		param->current_line[*i]))
	{
		if (ft_strchr("NSEW", param->current_line[*i]))
		{
			if (param->pos.y == -1)
			{
				param->pos.y = *i;
				set_direction(param, param->current_line[*i]);
				param->current_line[*i] = '0';
			}
			else
				ft_error("several players in the map", param);
		}
		(*i)++;
	}
	return ;
}

//check if line contains just "01NSEW \n and if there is only one player"
void	check_line(t_param *param)
{
	int	i;

	i = 0;
	skip_space(param->current_line, &i);
	if (!param->current_line[i])
		ft_error("there is an empty line in the map descrition", param);
	check_char(&i, param);
	if (param->current_line[i] == '\n')
		param->current_line[i] = '\0';
	if (param->current_line[i])
		ft_error("only 01NSEW are accepted as symbol for the map", param);
	if (i > param->map_y)
		param->map_y = i;
	return ;
}

// /*copy line in param->map until the end of file fd*/
int	get_map(t_param *param)
{
	char	**temp;
	int		i;

	i = 0;
	while (param->current_line)
	{
		check_line(param);
		if (param->pos.y != -1 && param->pos.x == -1)
			param->pos.x = i;
		temp = param->map;
		param->map = malloc((++i + 1) * sizeof(char *));
		if (!param->map)
			return (clean_map(temp));
		copy_map(param, temp);
		param->current_line = get_next_line(param->fd, 0);
	}
	param->map_x = i;
	return (0);
}

bool	closed_map(t_param *param, int max_x, int x, int y)
{
	if (x == 0 || y == 0 || x == max_x - 1 || y == param->map_x - 1)
		return (false);
	if (!param->map[y][x - 1] || param->map[y][x - 1] == ' '
		|| !param->map[y][x + 1] || param->map[y][x + 1] == ' ')
		return (false);
	if (!param->map[y - 1][x] || param->map[y - 1][x] == ' '
		|| !param->map[y + 1][x] || param->map[y + 1][x] == ' ')
		return (false);
	if (!param->map[y - 1][x - 1] || param->map[y - 1][x - 1] == ' '
		|| !param->map[y - 1][x + 1] || param->map[y - 1][x + 1] == ' ')
		return (false);
	if (!param->map[y + 1][x - 1] || param->map[y + 1][x - 1] == ' '
		|| !param->map[y + 1][x + 1] || param->map[y + 1][x + 1] == ' ')
		return (false);
	return (true);
}

int	check_map(t_param *param)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (param->pos.x == -1 || param->pos.y == -1)
		ft_error("no player in the map \
		(player must be symbolised by N, S, W or E)", param);
	while (param->map[y])
	{
		while (param->map[y][x])
		{
			if (ft_strchr("SNEW0", param->map[y][x])
			&& closed_map(param, ft_strlen(param->map[y]), x, y) == false)
				ft_error("map is not closed", param);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

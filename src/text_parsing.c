#include "../cub.h"

int	get_color(t_param *param)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 1;
	if (skip_space(param->current_line, &i) == 0 && get_number(&r, param->current_line, &i) != -1 \
		&& get_number(&g, param->current_line, &i) != -1 && get_number(&b, param->current_line, &i) != -1)
	{
		if (param->current_line[0] == 'F')
		{
			param->color_floor = create_rgb(r, g, b);
			param->format[4] = 1;
		}
		else if (param->current_line[0] == 'C')
		{
			param->color_ceiling = create_rgb(r, g, b);
			param->format[5] = 1;
		}
		return (0);
	}
	else
		ft_error("RGB number is incorrect", param);
	return (-1);
}

//keep the path
int	get_path(char second_letter, int i, t_param *param)
{
	int	j;

	j = 1;
	if (param->current_line[j] == second_letter)
		j++;
	if (!ft_strchr(" \t\n\v\r", param->current_line[j]))
		return (-1);
	while (ft_strchr(" \t\n\v\r", param->current_line[j]))
		j++;
	if (!param->current_line[j])
		return (-1);
	param->tex[i].path = ft_strdup(param->current_line + j);
	j = 0;
	while (!ft_strchr(" \t\n\v\r", param->tex[i].path[j]))
		j++;
	param->tex[i].path[j] = '\0';
	param->format[i] = 1;
	return (0);
}

int	keep_format(t_param *param)
{
	char	second_letter;
	int		i;

	second_letter = 'O';
	i = 0;
	if ((*param->current_line == 'F' && param->format[4] == 0)
		|| (*param->current_line == 'C' && param->format[5] == 0))
		return (get_color(param));
	else if (*param->current_line == 'E')
	{
		second_letter = 'A';
		i++;
	}
	else if (*param->current_line == 'S')
		i = 2;
	else if (*param->current_line == 'W')
	{
		second_letter = 'E';
		i = 3;
	}
	else if (*param->current_line != 'N' || param->format[i] == 1)
		return (-1);
	return (get_path(second_letter, i, param));
}

/*check_format :
	- check if there is a line which begin by NO/SO/WE/EA/F or C and
	add informations found after in param
	- swap lines with other things and spaces before the format description*/
int	check_format(t_param *param)
{
	int	i;

	i = 0;
	while (param->current_line[i] && ft_strchr(" \t\n\v\r", param->current_line[i]))
		i++;
	if (!param->current_line[i])
		return (0);
	if (ft_strchr("NSWEFC", param->current_line[i]))
		return (keep_format(param));
	else
		return (1);
}

void	check_texture(t_param *param)
{
	int		map;

	map = 0;
	param->current_line = get_next_line(param->fd, 0);
	while (param->current_line)
	{
		map = check_format(param);
		if (map == -1 || (map == 1 && (texture_parsed(param) != 6
					|| get_map(param) == -1 || check_map(param) == -1)))
			ft_error("Invalid texture format(NO/SO/E/W/F/C)", param);
		if (param->current_line && map != 1)
		{
			free(param->current_line);
			param->current_line = NULL;
		}
		param->current_line = get_next_line(param->fd, 0);
	}
	param->map = transpose_map(param->map, param->map_x, param->map_y);
	int tmp;
	tmp = param->map_x;
	param->map_x = param->map_y;
	param->map_y = tmp;
	tmp = param->pos.x;
	param->pos.x = param->pos.y;
	param->pos.y = tmp;
	tmp = param->dir.x;
	param->dir.x = param->dir.y;
	param->dir.y = tmp;
	tmp = param->plane.x;
	param->plane.x = param->plane.y;
	param->plane.y = tmp;

}

#include "../cub.h"

int	get_color(char *line, t_param *param)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 1;
	if (skip_space(line, &i) == 0 && get_number(&r, line, &i) != -1 \
		&& get_number(&g, line, &i) != -1 && get_number(&b, line, &i) != -1)
	{
		if (line[0] == 'F')
		{
			param->color_floor = create_rgb(r, g, b);
			param->format[4] = 1;
		}
		else if (line[0] == 'C')
		{
			param->color_ceiling = create_rgb(r, g, b);
			param->format[5] = 1;
		}
		return (0);
	}
	return (-1);
}

//keep the path
int	get_path(char *line, char second_letter, int i, t_param *param)
{
	int	j;

	j = 1;
	if (line[j] == second_letter)
		j++;
	if (!ft_strchr(" \t\n\v\r", line[j]))
		return (-1);
	while (ft_strchr(" \t\n\v\r", line[j]))
		j++;
	if (!line[j])
		return (-1);
	param->tex[i].path = ft_strdup(line + j);
	j = 0;
	while (!ft_strchr(" \t\n\v\r", param->tex[i].path[j]))
		j++;
	param->tex[i].path[j] = '\0';
	param->format[i] = 1;
	return (0);
}

int	keep_format(char *line, t_param *param)
{
	char	second_letter;
	int		i;

	second_letter = 'O';
	i = 0;
	if ((*line == 'F' && param->format[4] == 0) ||
		(*line == 'C' && param->format[5]== 0))
		return (get_color(line, param));
	else if (*line == 'E')
	{
		second_letter = 'A';
		i++;
	}
	else if (*line == 'S')
		i = 2;
	else if (*line == 'W')
	{
		second_letter = 'E';
		i = 3;
	}
	else if (*line != 'N' || param->format[i] == 1)
		return (-1);
	return (get_path(line, second_letter, i, param));
}

/*check_format :
	- check if there is a line which begin by NO/SO/WE/EA/F or C and
	add informations found after in param
	- swap lines with other things and spaces before the format description*/
int	check_format(char *line, t_param *param)
{
	int	i;

	i = 0;
	while (ft_strchr(" \t\n\v\r", line[i]))
		i++;
	if (!line[i])
		return (0);
	if (ft_strchr("NSWEFC", line[i]))
		return (keep_format(line, param));
	else
		return (1);
}

int	check_texture(t_param *param)
{
	char	*line;
	int		i;
	int		map;

	i = 0;
	map = 0;
	line = get_next_line(param->fd);
	while (line)
	{
		map = check_format(line, param);
		if (map == 1)
		{
			while (i < 6 && param->format[i] == 1)
				i++;
		}
		if (map == -1 || (map == 1 &&
			(i != 6 || get_map(param, line, param->fd) == -1
			|| check_map(param) == -1)))
			ft_error("miss something in texture description\nThe format should be NO/SO/WE/EA/C/F follow by the texture's path\\n", param);
		if (line && map != 1)
			free(line);
		line = get_next_line(param->fd);
	}
	return (0);
}

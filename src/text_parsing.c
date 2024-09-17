#include "cub.h"

int	get_color(char *line, t_param *param)
{
	int		r;
	int		g;
	int		b;
	char	*id;

	id = line++;
	if (skip_space(line) == 0 && get_number(&r, line) != -1 &&
		get_number(&g, line) != -1 && get_number(&b, line) != -1)
	{
		if (*id == "F")
		{
			param->color_floor = create_rgb(r, g, b);
			param->format[4] = 1;
		}
		else if (*id == "C")
		{
			param->color_ceiling = create_rgb(r, g, b);
			param->format[5] = 1;
		}
		line = id;//put the line at the beginning to be well freed
		return (0);
	}
	line = id;
	return (-1);
}

//keep the path
int	get_path(char *line, char second_letter, int i, t_param *param)
{
	int	j;

	j = 1;
	if (line[j] == second_letter)
		j++;
	if (!ft_strchr(" \t\n\v\r", line[j]))//no space after id
		return (-1);
	while (ft_strchr(" \t\n\v\r", line[j]))//skip space
		j++;
	if (!line[j])//no texture's path after spaces
		return (-1);
	param->tex[i].path = ft_strdup(line + j);
	param->format[i] = 1;
	return (0);
}

int	keep_format(char *line, t_param *param)
{
	char	second_letter;
	int		i;

	second_letter = "O";
	i = 0;
	if ((*line == "F" && param->format[4] == 0) ||
		(*line == "C" && param->format[5]== 0))
		return (get_color(line, param));
	else if (*line == "E")
	{
		second_letter = "A";
		i++;
	}
	else if (*line == "S")
		i = 2;
	else if (*line == "W")
	{
		second_letter = "E";
		i = 3;
	}
	else if (*line != "N" || param->format[i] == 1)
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
	char	*save_line;

	i = 0;
	map = 0;
	line = get_next_line(param->fd);
	while(line)
	{
		map = check_format(line, param);
		if (map == 1)//line not begin by NSWEFC
		{
			while(i < 6 && param->format[i] == 1)//check if all texture are filled
				i++;
		}
		if (map == -1 || (map == 1 &&
			(i != 5 || copy_map(param->map, line, param->fd) == -1
			|| check_map(param) == -1)))//wrong format, keep format return -1
			ft_error("miss something in texture description\nThe format should be NO/SO/WE/EA/C/F follow by the texture's path\\n", param);
		if (line)
			free(line);//map = 0, line is empty
		line = get_next_line(param->fd);
	}
}

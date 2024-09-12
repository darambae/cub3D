#include "../cub.h"

bool	load_texture(t_param *param)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		param->tex[i].img = mlx_xpm_file_to_image(param->mlx, \
			param->tex[i].path, &param->tex[i].w, &param->tex[i].h);
		if (!param->tex[i].img)
		{
			printf("Error: Unable to load t from %s\n", param->tex[i].path);
			return (false);
		}
		param->tex[i].addr = mlx_get_data_addr(param->tex[i].img, \
			&param->tex[i].bits_per_pixel, &param->tex[i].size_line, \
			&param->tex[i].endian);
		i++;
	}
	return (true);
}

int	check_extension(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 4)
		return (-1);
	if (ft_strncmp(av + (len - 4), ".cub", 4) =! 0)
		return (-1);
}

int	check_openable(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	return (fd);
}
int	get_path(char *line, char second_letter, int i, t_param *param)
{
	line++;
	if (*line == second_letter)
		line++;
	if (*line != " ")
		return (-1);
	while (ft_strchr(" \t\n\v\r", *line))
		line++;
	if (!*line)//no texture's path
		return (-1);
	//0 = north, 1 = east, 2 = south, 3 = west
	param->tex[i].path = ft_strdup(line);
	param->format[i] = 1;
	return (0);
}
int	keep_format(char *line, t_param *param)
{
	char	second_letter;
	int		i;

	second_letter = "O";
	i = 0;
	if (*line == "F" || *line == "C")
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
	return (get_path(line, second_letter, i, param));
}

/*check_format :
	- check if there is a line which begin by NO/SO/WE/EA/F or C and
	add informations found after in param
	- swap lines with other things and spaces before the format description*/
int	check_format(char *line, t_param *param)
{
	while (ft_strchr(" \t\n\v\r", *line))
		line++;
	if (!*line)
		return (0);
	if (*line && ft_strchr("NSWEFC", *line))
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
	save_line = NULL;
	line = get_next_line(param->fd);
	if (!line)
		return (-1);
	while(line)
	{
		save_line = line;
		map = check_format(line, param);
		if (map == -1);//wrong format
		{
			free(line);
			return (-1);
		}
		if (map == 1)//line not begin by NSWEFC
		{
			//check if all texture are filled
			while(i < 7 && param->format[i] == 1)
				i++;
			if (i < 6)
				return (-1);
			//copy map in a char ** to be manipulated and modified
			param->map = copy_map(line, param->fd);
			return (check_map(param));
		}
		free(line);
		line = get_next_line(param->fd);
	}
	return (-1);
}

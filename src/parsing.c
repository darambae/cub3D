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
	av = av + len - 4;
	if (ft_strncmp(av, ".cub", 4) =! 0)
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
	if (!ft_strchr(" \t\n\v\r", *line))//no space after id
		return (-1);
	while (ft_strchr(" \t\n\v\r", *line))//skip space
		line++;
	if (!*line)//no texture's path after spaces
		return (-1);
	param->tex[i].path = ft_strdup(line);
	param->format[i] = 1;
	return (0);
}
int	get_number(int *n, char *line)
{
	*n = 0;
	if (ft_isdigit(*line))
	{
		*n = ft_atoi(line);
		if (*n < 0 || *n > 255)
			return (-1);
		while (ft_isdigit(*line))
			line++;
		if (*line == "," && *(line + 1) == " ")
		{
			line = line + 2;
			return (0);
		}
		else
			return (-1);
	}
}
int	get_color(char *line, t_param *param)
{
	int		r;
	int		g;
	int		b;
	char	id;

	id = *line;
	if ((id == "F" && param->format[4] == 0) ||
		(id == "C" && param->format[5]== 0))
	{
		line++;
		if (!ft_strchr(" \t\n\v\r", *line))//no space after id
			return (-1);
		while (ft_strchr(" \t\n\v\r", *line))//skip space
			line++;
		if (!*line)//no color after spaces
			return (-1);
		if (get_number(&r, line) != -1)
		{
			if (get_number(&g, line) != -1)
			{
				if (get_number(&b, line) != -1)
				{
					if (id == "F")
					{
						param->color_floor = create_rgb(r, g, b);
						param->format[4] = 1;
					}
					if (id == "C")
					{
						param->color_ceiling = create_rgb(r, g, b);
						param->format[5] = 1;
					}
					return (0);
				}
			}
		}
	}
	return (-1);
}
int	keep_format(char *line, t_param *param)
{
	char	second_letter;
	int		i;

	second_letter = "O";
	i = 0;
	if (*line == "F" || *line == "C")
		return (get_color(line, param));
	else if (*line == "E" && param->format[1] == 0)
	{
		second_letter = "A";
		i++;
	}
	else if (*line == "S" && param->format[2] == 0)
		i = 2;
	else if (*line == "W" && param->format[3] == 0)
	{
		second_letter = "E";
		i = 3;
	}
	if (param->format[i] == 1)
		return (-1);
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

//free la map
int	clean_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
	return (-1);
}
//check if line contains just "01NSEW \n"
int	check_line(char *line)
{
	int	i;

	i = 0;
	while(line[i] &&
		(ft_strchr("01NSEW", line[i]) || ft_strchr(" \t\n\v\r", line[i])))
		i++;
	if (line[i])
		return (-1);
	return (0);
}

char	**copy_map(char *line, int fd)
{
	char	**map;
	char	**temp;
	int		i;
	int		j;

	map = NULL;
	i = 2;
	map = malloc(i * sizeof(char *));
	if (!map)
		return (NULL);
	map[0] = line;
	map[1] = '\0';
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line) == -1)
			return (clean_map(map));
		i++;
		temp = map;
		map = malloc(i * sizeof(char *));
		if (!map)
		{
			clean_map(temp);
			return (NULL);
		}
		while (j < i - 1)
			map[j++] = temp[i];
		map[j++] = line;
		map[j] = '\0';
		free(temp);
		line = get_next_line(fd);
	}
	return (map);
}

int	ft_flood_map(char **map)
{

}

int	ft_map_is_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_flood_map(map) > 0)
	{
		while (map[i])
		{
			while (map[i][j])
			{
				if (ft_strchr("SNEW0", map[i][j]))
					return (-1);//if all is not 1, wall are not closed
				j++;
			}
			j = 0;
			i++;
		}
	}
	return (-1);//flood_map detect an error (several player or wall not closed)
}

int	check_map(t_param *param)
{
	char	**mini_map;
	int		i;

	i = 0;
	mini_map = NULL;
	mini_map = malloc(param->map_w * sizeof(char *));
	if (!mini_map)
		return (-1);
	while (i < param->map_w)
	{
		mini_map[i] = ft_strdup(param->map[i]);
		i++;
	}
	mini_map[i] = '\0';
	if (ft_map_is_closed(param->map) == -1)
		return (clean_map(param->map), clean_map(mini_map));
	clean_map(param->map);
	param->map = mini_map;
	//faire un flood_fill sur la map et verif a la fin qu'il n'y a que des 1
	//si NSW ou E, utiliser un booleen pour verifier qu'il n'y en a qu'un

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
			while(i < 6 && param->format[i] == 1)
				i++;
			if (i != 5)
				return (-1);
			//copy map in a char ** to be manipulated and modified
			param->map = copy_map(save_line, param->fd);
			param->map_w = i;
			return (check_map(param));
		}
		free(line);
		line = get_next_line(param->fd);
	}
	return (-1);
}

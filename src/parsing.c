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

int	keep_format(char *line, t_param *param)
{

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
	if (line[i] && ft_strchr("NSWEFC", line[i]))
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
	if (!line)
		return (-1);
	while(line)
	{
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

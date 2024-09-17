#include "cub.h"


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
		if (map == -1);//wrong format, keep format return -1
		{
			free(line);
			line = NULL;
			return (-1);
		}
		if (map == 1)//line not begin by NSWEFC
		{
			//check if all texture are filled
			while(i < 6 && param->format[i] == 1)
				i++;
			if (i != 5)
			{
				free(line);
				line = NULL;
				return (-1);
			}
			if (copy_map(param->map, line, param->fd) == 0)
				return (check_map(param));
			return (-1);
		}
		free(line);//map = 0, line is empty
		line = get_next_line(param->fd);
	}
	close(param->fd);
	return (-1);
}

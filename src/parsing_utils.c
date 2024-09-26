#include "../cub.h"

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

int	get_number(int *n, char *line, int *i)
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

//free la map
int	clean_map(char **map, int max)
{
	int	i;

	i = 0;
	while (i < max && map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
	return (-1);
}

void	set_direction(t_param *param, char c)
{
	if (c == 'E')
		param->dir.x++;
	else if (c == 'W')
		param->dir.x--;
	else if (c == 'S')
		param->dir.y--;
	else if (c == 'N')
		param->dir.y++;
	if (param->dir.y > 0)
		param->plane.x = param->fov * -1;
	else if (param->dir.y < 0)
		param->plane.x = param->fov;
	else if (param->dir.x > 0)
		param->plane.y = param->fov;
	else if (param->dir.x < 0)
		param->plane.y = param->fov * -1;
}

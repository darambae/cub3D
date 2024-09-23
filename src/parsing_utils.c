#include "../cub.h"

int	skip_space(char *line, int *i)
{
	if (!ft_strchr(" \t\n\v\r", line[*i]))//no space after id
		return (-1);
	while (ft_strchr(" \t\n\v\r", line[*i]))//skip space
		(*i)++;
	if (!line[*i])//no color after spaces
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

/*char 	**invert_map(t_param *param)
{
	char	**invert_map;
	int		i;
	int		j;

	j = 0;
	i = 0;
	invert_map = malloc(param->map_x * sizeof(char*));
	if (!invert_map)
		ft_error("memorie allocation failed", param);
	while (j < param->map_x)
	{
		invert_map[j] = malloc(param->map_y * sizeof(char));
			if (!invert_map[j])
				ft_error("memorie allocation failed", param);
		j++;
	}
	j = 0;
	while (param->map[i])
	{
		while (param->map[i][j])
		{
			invert_map[j][i] = param->map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (invert_map);
}*/

#include "../cub.h"

int	skip_space(char **line)
{
	if (!ft_strchr(" \t\n\v\r", **line))//no space after id
		return (-1);
	while (ft_strchr(" \t\n\v\r", **line))//skip space
		(*line)++;
	if (!*line)//no color after spaces
		return (-1);
	return (0);
}

int	get_number(int *n, char **line)
{
	*n = 0;
	if (**line == ',')
			(*line)++;
	if (ft_isdigit(**line))
	{
		*n = ft_atoi(*line);
		if (*n < 0 || *n > 255)
			return (-1);
		while (ft_isdigit(**line))
			(*line)++;
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

#include "../cub.h"

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

//copy_map create a char ** to be manipulated and modified and if charac are whitespace or SNEW01
int	copy_map(char **map, char *line, int fd)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line)
	{
		if (check_line(line) == -1)
			return (clean_map(map));
		temp = map;
		map = malloc((++i + 1) * sizeof(char *));
		if (!map)
			return (clean_map(temp));
		while (j < i - 1)
			map[j] = temp[j++];
		map[j++] = line;
		map[j] = '\0';
		if (temp)
			free(temp);
		line = get_next_line(fd);
		j = 0;
		temp = NULL;
	}
	return (0);
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
//check if the map have only one player and is closed
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
	close(param->fd);
}

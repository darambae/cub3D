#include "../cub.h"

//check if line contains just "01NSEW \n and if there is only one player"
void	check_line(char *line, t_param *param)
{
	int	i;

	i = 0;
	skip_space(line, &i);
	if (!line[i])
		ft_error("there is an empty line in the map descrition", param);
	while (line[i] && ft_strchr("01NSEW \n", line[i]))
	{
		if (ft_strchr("NSEW", line[i]))
		{
			if (param->pos.y == -1)
			{
				param->pos.y = i;
				set_direction(param, line[i]);
				line[i] = '0';
			}
			else
				ft_error("several players in the map", param);
		}
		i++;
	}
	if (line[i])
		ft_error("only 01NSEW are accepted as symbol for the map", param);
	if (i > param->map_y)
		param->map_y = i;
	return ;
}

// /*copy temp in map and add line at the end*/
void	copy_map(char **map, char **temp, char *line)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			map[i] = temp[i];
			i++;
		}
	}
	map[i++] = line;
	map[i] = '\0';
	if (temp)
		free(temp);
	temp = NULL;
}

// /*copy line in param->map until the end of file fd*/
int	get_map(t_param *param, char *line, int fd)
{
	char	**temp;
	int		i;

	i = 0;
	while (line)
	{
		check_line(line, param);
		if (param->pos.y != -1 && param->pos.x == -1)
			param->pos.x = i;
		temp = param->map;
		param->map = malloc((++i + 1) * sizeof(char *));
		if (!param->map)
			return (clean_map(temp));
		copy_map(param->map, temp, line);
		line = get_next_line(fd);
	}
	close(param->fd);
	param->map_x = i;
	return (0);
}

bool	closed_map(t_param *param, int x, int y)
{
	if (x == 0 || y == 0 || x == param->map_y || y == param->map_x)
		return (false);
	if (param->map[y][x - 1] == ' ' || param->map[y][x + 1] == ' ')
		return (false);
	if (param->map[y - 1][x] == ' ' || param->map[y + 1][x] == ' ')
		return (false);
	if (param->map[y - 1][x - 1] == ' ' || param->map[y - 1][x + 1] == ' ')
		return (false);
	if (param->map[y + 1][x - 1] == ' ' || param->map[y + 1][x + 1] == ' ')
		return (false);
	return (true);
}


int	check_map(t_param *param)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (param->pos.x == -1 || param->pos.y == -1)
		ft_error("no player in the map \
		(player must be symbolised by N, S, W or E)", param);
	while (param->map[y])
	{
		while (param->map[y][x])
		{
			if (ft_strchr("SNEW0", param->map[y][x])
			&& closed_map(param, x, y) == false)
				ft_error("map is not closed", param);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
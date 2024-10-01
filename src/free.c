#include "../cub.h"

//free la map
int	clean_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
	return (-1);
}

void	clean_tex(t_param *param)
{
	int	i;

	i = 0;
	while (i < 4 && param->tex[i].path)
	{
		free(param->tex[i].path);
		param->tex[i].path = NULL;
		if (param->tex[i].img)
			mlx_destroy_image(param->mlx, param->tex[i].img);
		i++;
	}
	free(param->tex);
	param->tex = NULL;
}

void	clean_mlx(t_param *param)
{
	if (param->window)
	{
		mlx_destroy_window(param->mlx, param->window);
		param->window = NULL;
	}
	if (param->img)
	{
		mlx_destroy_image(param->mlx, param->img);
		param->img = NULL;
	}
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	param->mlx = NULL;
}

void	clean_all(t_param *param)
{
	if (param)
	{
		if (param->tex[0].path)
			clean_tex(param);
		if (param->tex)
			free(param->tex);
		if (param->mlx)
			clean_mlx(param);
		if (param->format)
		{
			free(param->format);
			param->format = NULL;
		}
		if (param->map)
			clean_map(param->map);
		if (param->current_line)
		{
			free(param->current_line);
			param->current_line = NULL;
		}
		if (param->mlx)
			clean_mlx(param);
	}
	free(param);
	param = NULL;
}

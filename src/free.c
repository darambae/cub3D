#include "../cub.h"


void	clean_tex(t_texture *tex, t_param *param)
{
	int	i;

	i = 0;
	while (tex[i].path && i < 4)
	{
		free(tex[i].path);
		tex[i].path = NULL;
		mlx_destroy_image(param->mlx, tex[i].img);
		free(tex[i].addr);
		i++;
	}
	free(tex);
	tex = NULL;
}

void	clean_mlx(t_param *param)
{
	if (param->mlx)
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
		if (param->addr)
		{
			free(param->addr);
			param->addr = NULL;
		}
	}
	mlx_destroy_display(param->mlx);
	param->mlx = NULL;
}

void	clean_all(t_param *param)
{
	if (param)
	{
		if (param->mlx)
			clean_mlx(param);
		if (param->format)
		{
			free(param->format);
			param->format = NULL;
		}
		if (param->map)
			clean_map(param->map);
		if (param->tex)
			clean_tex(param->tex, param);
	}
	free(param);
	param = NULL;
}
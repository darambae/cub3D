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
			ft_error("Error: Unable to load texture file.", param);
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
	int	cmp;

	len = ft_strlen(av);
	if (len < 4)
		return (-1);
	av = av + len - 4;
	cmp = ft_strncmp(av, ".cub", 4);
	if (cmp != 0)
		return (-1);
	return (0);
}

int	check_openable(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	return (fd);
}

void	parse_map_file(t_param *param, char **av)
{
	if (check_extension(av[1]) < 0)
		ft_error("filename must finish by .cub", param);
	param->fd = check_openable(av[1]);
	if (param->fd < 0)
		ft_error("file is not openable", param);
	check_texture(param);
	if (!param->map)
		ft_error("no map in the file.cub", param);
}

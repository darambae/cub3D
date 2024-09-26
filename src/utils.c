#include "../cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlxx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * SCREEN_W + x) * (param->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	ft_error(char *str, t_param *param)
{
	close(param->fd);
	clean_all(param);
	printf("ERROR: %s\n", str);
	exit (1);
}

int	texture_parsed(t_param *param)
{
	int	i;

	i = 0;
	while (i < 6 && param->format[i] == 1)
		i++;
	return (i);
}

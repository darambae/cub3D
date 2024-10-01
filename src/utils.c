/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:25:45 by dabae             #+#    #+#             */
/*   Updated: 2024/10/01 14:25:46 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (param->fd > 0)
	{
		get_next_line(param->fd, 1);
		close(param->fd);
	}
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

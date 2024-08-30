#ifndef CUB_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include "../mlx_linux/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

#define SCREEN_W 640
#define SCREEN_H 480

typedef struct s_map
{
	double	x;
	double	y;
	double	z;
}			t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_param
{
	void	*mlx;
	void	*window;
	t_map	**map;
	int		map_width;
	int		map_lenth;
	double	fov;
	t_map	*pos;
	t_map	*plane;
	t_map	*dir;
	int		color_floor;
	int		color_ceiling;

}	t_param;

//vector calculation
t_vector	addVectors(t_vector a, t_vector b);
t_vector	subVectors(t_vector a, t_vector b);
t_vector	scaleVectors(t_vector a, double n);

//initializing parameters by reading .cub file
void	init_param(t_param *param);
int		create_rgb(int r, int g, int b);

void	draw_line(t_param param);

#endif // !CUB_H

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include "../mlx_linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# define SCREEN_W 512
# define SCREEN_H 512

# define LEFT 97
# define RIGHT 100
# define BACK	115
# define FORWARD 119
# define ESC 65307
# define LOOK_LEFT	65361
# define LOOK_RIGHT	65363

extern int	world_map[9][18];

typedef struct s_vec
{
	double	x;
	double	y;
}			t_vec;

typedef struct s_texture
{
	char	*path;
	int		w;
	int		h;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_param
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;

	int			map_w;
	int			map_l;
	double		fov;
	t_vec		*pos;
	t_vec		*plane;
	t_vec		*dir;
	t_vec		ray_dir;
	int			side;
	int			color_floor;
	int			color_ceiling;
	t_texture	*tex;
	int			draw_start;
	int			draw_end;
	int			size_line;
	int			endian;
}	t_param;

//map parsing

//vector calculation
t_vec	addVectors(t_vec a, t_vec b);
t_vec	subVectors(t_vec a, t_vec b);
t_vec	scaleVectors(t_vec a, double n);

//initializing parameters by reading .cub file
void	init_param(t_param *param);
int		create_rgb(int r, int g, int b);

void	draw_line(t_param *param);
int		move_back_forward(t_param *param, bool forward);
int		move_left_right(t_param *param, bool right);
void	rotate(t_param *param, double angle);
void	event_handler(t_param *param);

int		create_rgb(int r, int g, int b);

#endif

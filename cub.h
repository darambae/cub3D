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
# include "./mlx_linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# define SCREEN_W 800
# define SCREEN_H 800

# define LEFT 97
# define RIGHT 100
# define BACK	115
# define FORWARD 119
# define ESC 65307
# define LOOK_LEFT	65361
# define LOOK_RIGHT	65363
# define PI 3.14159

typedef struct s_vec
{
	double	x;
	double	y;
}			t_vec;

typedef struct s_mini
{
	double	scale;
	int		color;
}	t_mini;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	t_vec	step;
	t_vec	map;
	double	camera_x;
	double	perp_wall_dist;
	int		line_height;
	int		side;
	int		draw_start;
	int		draw_end;
}	t_ray;

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
	int		line_height;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	double	wall_x;
}	t_texture;

typedef struct s_param
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			fd;
	int			*format;
	char		**map;
	char		*current_line;
	int			map_y;
	int			map_x;
	double		fov;
	t_vec		pos;
	t_vec		plane;
	t_vec		dir;
	int			color_floor;
	int			color_ceiling;
	t_texture	*tex;
	int			size_line;
	int			endian;
	t_ray		ray;
	t_mini		mini;
}	t_param;

//parsing
void			parse_map_file(t_param *param, char **av);

//texture path and color parsing
int				get_color(char *line, t_param *param);
int				get_path(char *line, char second_letter, int i, t_param *param);
int				keep_format(char *line, t_param *param);
int				check_format(char *line, t_param *param);
void			check_texture(t_param *param);
int				skip_space(char *line, int *i);
int				get_number(int *n, char *line, int *i);

//map parsing
int				clean_map(char **map);
void			check_line(t_param *param);
void			copy_map(t_param *param, char **temp);
int				get_map(t_param *param);
bool			closed_map(t_param *param, int max_x, int x, int y);
int				check_map(t_param *param);
void			set_direction(t_param *param, char c);
int				texture_parsed(t_param *param);

//vector calculation
t_vec			add_vec(t_vec a, t_vec b);
t_vec			sub_vec(t_vec a, t_vec b);
t_vec			scale_vec(t_vec a, double n);

// initializing parameters by reading .cub file
void			init_param(t_param *param);
bool			load_texture(t_param *param);
int				create_rgb(int r, int g, int b);
bool			set_screen(t_param *param);
void			cast_rays_and_render(t_param *param);
void			move_back_forward(t_param *param, bool forward);
void			move_left_right(t_param *param, bool right);
void			rotate(t_param *param, double angle);
void			event_handler(t_param *param);
void			verline(t_param *param, int x, t_texture t);
t_texture		get_wall_dir(t_param *param);
int				get_text_pix(t_ray r, int y, t_texture t);
void			setup_ray(t_param *param, int cur);

//calculation
void			get_perp_wall_dist(t_param *param);

//utils
int				create_rgb(int r, int g, int b);
void			my_mlxx_pixel_put(t_param *param, int x, int y, int color);

//error management
void			ft_error(char *str, t_param *param);
void			clean_all(t_param *param);
void			clean_mlx(t_param *param);
void			clean_tex(t_param *param);

//bonus
void			print_minimap(t_param *param);

#endif

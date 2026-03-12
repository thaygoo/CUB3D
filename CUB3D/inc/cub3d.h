/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:41 by huburton          #+#    #+#             */
/*   Updated: 2026/03/12 20:53:29 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../src/libft/libft.h"
# include "../src/minilibx-linux/mlx.h"

# define WIDTH	512
# define HEIGHT	512
# define BLOCK	64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359f

typedef struct s_map
{
	char	**grid;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_player
{
	int		radius;
	float	x;
	float	y;
	float	angle;
	float	step;
	float	angle_speed;
	bool	key_w;
	bool	key_a;
	bool	key_s;
	bool	key_d;
	bool	key_left;
	bool	key_right;
	int		left;
	int		right;
	int		top;
	int		bottom;
}	t_player;

typedef struct s_ray
{
	float	px;
	float	py;
	float	dx;
	float	dy;
	int		mapx;
	int		mapy;
	float	delta_dist_x;
	float	delta_dist_y;
	int		stepx;
	int		stepy;
	float	side_dist_x;
	float	side_dist_y;
	float	dist;
	int		hit;
	float	hitx;
	float	hity;
	int		side;
	float	angle;
}	t_ray;

typedef struct s_line
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
}	t_line;

typedef enum s_tex_id
{
	NORTH	= 0,
	SOUTH	= 1,
	WEST	= 2,
	EAST	= 3
}	t_tex_id;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct	s_texture_sample
{
	float	slice_width;
	int		screen_x;
	float	perp_dist;
	int		line_height;
	int		start;
	int		end;
	int		ceil_color;
	int		floor_color;
	int		tex_id;
	float	wall_x;
	int		tex_x;
	int		tex_y;
	int		tex_start;
	char	*pixel;
	int		color;
}	t_texture_sample;

typedef struct s_data
{
	t_map		map;
	t_tex		tex[4];
	t_player	p;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bit_per_pixel;
	int			size_line;
	int			endian;
}	t_data;

int		check_args(int argc, char **argv);
int		check_extension(char *filename);
int		parse_map(char *filename, t_data *data);
char	**read_file_lines(char *filename);
int		extract_elements(char **lines, t_data *data, int *map_start_idx);
int		extract_grid(char **lines, t_data *data, int start_idx);
int		validate_map(t_data *data);
int		find_player(t_data *data);

void	free_data(t_data *data);
void	free_split(char **split);
int		is_whitespace(char c);

void	put_pixel(t_data *data, int x, int y, int color);
void	draw_circle(t_data *data, int cx, int cy, int r);
void	draw_square(t_data *data, int x, int y, int size);
void	draw_map(t_data *data);
void	draw_ray_line(t_data *data, float x1, float y1, int color);
bool	touch(float px, float py, t_data *data);
// void	cast_ray(t_data *data, float angle, int color);
// void	cast_rays(t_data *data, int fov);
void	cast_rays(t_data *data);
void	load_textures(t_data *data);

int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press_debug(int keycode, t_data *data);
int		key_release_debug(int keycode, t_data *data);
void	move_player(t_data *data);

#endif

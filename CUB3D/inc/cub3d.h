/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:41 by huburton          #+#    #+#             */
/*   Updated: 2026/03/05 15:32:14 by msochor          ###   ########.fr       */
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

# define WIDTH	1025
# define HEIGHT	513
# define BLOCK	64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

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
	bool	key_W;
	bool	key_A;
	bool	key_S;
	bool	key_D;
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
	int		mapX;
	int		mapY;
	float	deltaDistX;
	float	deltaDistY;
	int		stepX;
	int		stepY;
	float	sideDistX;
	float	sideDistY;
	float	dist;
	float	hitX;
	float	hitY;
	int		side;
}	t_ray;

typedef struct s_line
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
} t_line;

typedef struct s_data
{
	t_map		map;
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
// void	draw_line(t_data *data, float x0, float y0, float x1, float y1, int color);
void	draw_ray_line(t_data *data, float x1, float y1, int color);
bool	touch(float px, float py, t_data *data);
void	cast_ray(t_data *data);

int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press_debug(int keycode, t_data *data);
int		key_release_debug(int keycode, t_data *data);
void	move_player(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:55 by huburton          #+#    #+#             */
/*   Updated: 2026/02/26 17:42:33 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_data *data)
{
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.no_texture = NULL;
	data->map.so_texture = NULL;
	data->map.we_texture = NULL;
	data->map.ea_texture = NULL;
	data->map.floor_color[0] = -1;
	data->map.floor_color[1] = -1;
	data->map.floor_color[2] = -1;
	data->map.ceiling_color[0] = -1;
	data->map.ceiling_color[1] = -1;
	data->map.ceiling_color[2] = -1;
	data->map.player_x = -1;
	data->map.player_y = -1;
	data->map.player_dir = '\0';
}

void	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	// data->addr = mlx_get_data_addr(data->img_ptr, &data->bit_per_pixel,
	// 		&data->size_line, &data->endian);
	// init_player(data);
}

void	init_player(t_data *data)
{
	data->player.x = WIDTH / 2;
	data->player.y = HEIGHT / 2;
	data->player.angle = 3 * PI / 2;
	data->player.key_W = false;
	data->player.key_A = false;
	data->player.key_S = false;
	data->player.key_D = false;
	data->player.key_left = false;
	data->player.key_right = false;
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int index;
	
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * data->size_line + x * data->bit_per_pixel / 8;
	data->addr[index] = color & 0xFF;
	data->addr[index + 1] = (color >> 8) & 0xFF;
	data->addr[index + 2] = (color >> 16) & 0xFF;
}

void    draw_circle(t_data *data, int cx, int cy, int r, int color)
{
	const double step = 0.01;          // smaller step → smoother circle
	for (double angle = 0; angle < 2 * PI; angle += step)
	{
		int x = cx + (int)(r * cos(angle));
		int y = cy + (int)(r * sin(angle));
		put_pixel(data, x, y, color);
	}
}

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (i < size)
	{	
		put_pixel(data, x + i, y, color);
		put_pixel(data, x, y + i, color);
		put_pixel(data, x + i, y + size, color);
		put_pixel(data, x + size, y + i, color);
		i++;
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->player.key_W = true;
		printf("W pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == A)
	{
		data->player.key_A = true;
		printf("A pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == S)
	{
		data->player.key_S = true;
		printf("S pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == D)
	{
		data->player.key_D = true;
		printf("D pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == LEFT)
	{
		data->player.key_left = true;
		printf("LEFT pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == RIGHT)
	{
		data->player.key_right = true;
		printf("LEFT pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->player.key_W = false;
		printf("W released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == A)
	{
		data->player.key_A = false;
		printf("A released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == S)
	{
		data->player.key_S = false;
		printf("S released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == D)
	{
		data->player.key_D = false;
		printf("D released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
		if (keycode == LEFT)
	{
		data->player.key_left = false;
		printf("LEFT released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	if (keycode == RIGHT)
	{
		data->player.key_right = false;
		printf("LEFT released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
		printf("player ANGLE: %f\n", data->player.angle);
	}
	return (0);
}

bool	touch(float px, float py, t_data *data)
{
	int	x;
	int	y; 

	x = px / BLOCK;
	y = py / BLOCK;
	if (data->map.grid[y][x] == '1')
		return (true);
	return (false);
}

void	move_player(t_data *data)
{
	int		step;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	step = 1;
	angle_speed = 0.01;	
	if(data->player.key_left)
		data->player.angle -= angle_speed;
	if(data->player.key_right)
		data->player.angle += angle_speed;
	if (data->player.angle > 2 * PI)
		data->player.angle = 0;
	if (data->player.angle < 0)
		data->player.angle = 2 * PI;
	cos_angle = cos(data->player.angle);
	sin_angle = sin(data->player.angle);
	if (data->player.key_W)
	{
		if (!touch(data->player.x + cos_angle * step, data->player.y + sin_angle * step, data))
		{	
			data->player.x += cos_angle * step;
			data->player.y += sin_angle * step;
		}
	}
	if (data->player.key_S)
	{
		if (!touch(data->player.x - cos_angle * step, data->player.y - sin_angle * step, data))
		{
			data->player.x -= cos_angle * step;
			data->player.y -= sin_angle * step;	
		}
	}
	if (data->player.key_A)
	{
		if (!touch(data->player.x + sin_angle * step, data->player.y - cos_angle * step, data))
		{
			data->player.x += sin_angle * step;
			data->player.y -= cos_angle * step;
		}
	}
	if (data->player.key_D)
	{
		if (!touch(data->player.x - sin_angle * step, data->player.y + cos_angle * step, data))
		{
			data->player.x -= sin_angle * step;
			data->player.y += cos_angle * step;
		}
	}
	// if (data->player.key_W)
	// {
	// 	if (data->player.y - step >= 0)
	// 		data->player.y -= step;
	// }
	// if (data->player.key_S)
	// {
	// 	if (data->player.y + step <= HEIGHT)
	// 		data->player.y += step;
	// }
	// if (data->player.key_A)
	// {
	// 	if (data->player.x - step >= 0)
	// 		data->player.x -= step;
	// }
	// if (data->player.key_D)
	// {
	// 	if (data->player.x + step <= WIDTH)
	// 		data->player.x += step;
	// }
	
	// if (data->player.key_W)
	// {
	// 	if ((data->player.x + cos_angle * step) <= WIDTH)
	// 		data->player.x += cos_angle * step;
	// 	if ((data->player.y + sin_angle * step) <= HEIGHT)
	// 		data->player.y += sin_angle * step;
	// }
	// if (data->player.key_S)w
	// {
	// 	if ((data->player.x - cos_angle * step) >= 0)
	// 		data->player.x -= cos_angle * step;
	// 	if ((data->player.y - sin_angle * step) >= 0)
	// 		data->player.y -= sin_angle * step;
	// }
	// if (data->player.key_A)
	// {
	// 	if ((data->player.x + sin_angle * step) <= WIDTH)
	// 		data->player.x += sin_angle * step;
	// 	if ((data->player.y - cos_angle * step) >= 0)
	// 		data->player.y -= cos_angle * step;
	// }
	// if (data->player.key_D)
	// {
	// 	if ((data->player.x - sin_angle * step) >= 0)
	// 		data->player.x -= sin_angle * step;
	// 	if ((data->player.y + cos_angle * step) <= HEIGHT)
	// 		data->player.y += cos_angle * step;
	// }
}

void	draw_map(t_data *data)
{
	char	**grid;
	int		color;
	int		x;
	int		y;
	
	
	color = 0xFFFFFF;
	grid = data->map.grid;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '1')
				draw_square(data, x * BLOCK, y * BLOCK, BLOCK, color);
			x++; 
		}
		y++;
	}	
}
// void clear_image(t_data *data)
// {
// 	ft_memset(data->addr, 0, HEIGHT * data->size_line);
// }


int	draw_loop(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bit_per_pixel,
			&data->size_line, &data->endian);
	// clear_image(data);
	move_player(data);
	// draw_square(data, data->player.x -5, data->player.y -5, 10, 0x00FF00);
	draw_circle(data, data->player.x, data->player.y, 10, 0x00FF00);
	draw_map(data);
	
	float	ray_x = data->player.x;
	float	ray_y = data->player.y;
	float	cos_angle = cos(data->player.angle);
	float	sin_angle = sin(data->player.angle);

	while (!touch(ray_x, ray_y, data))
	{
		put_pixel(data, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);	
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
		return (1);
	init_data(&data);
	if (parse_map(argv[1], &data) != 0)
		return (1);
	printf("Success: Map loaded\n");
	
	init_game(&data);
	init_player(&data);
	
	mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, draw_loop, &data);


	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
}

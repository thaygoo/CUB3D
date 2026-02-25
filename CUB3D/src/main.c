/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:55 by huburton          #+#    #+#             */
/*   Updated: 2026/02/25 19:00:06 by msochor          ###   ########.fr       */
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
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bit_per_pixel,
			&data->size_line, &data->endian);
	// init_player(data);
}

void	init_player(t_data *data)
{
	data->player.x = WIDTH / 2;
	data->player.y = HEIGHT / 2;
	data->player.angle = 0;
	data->player.key_W = false;
	data->player.key_A = false;
	data->player.key_S = false;
	data->player.key_D = false;
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

void	draw_square(t_data *data, int x, int y, int color, int size)
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
	}
	if (keycode == A)
	{
		data->player.key_A = true;
		printf("A pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
	}
	if (keycode == S)
	{
		data->player.key_S = true;
		printf("S pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
	}
	if (keycode == D)
	{
		data->player.key_D = true;
		printf("D pressed\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
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
	}
	if (keycode == A)
	{
		data->player.key_A = false;
		printf("A released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
	}
	if (keycode == S)
	{
		data->player.key_S = false;
		printf("S released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
	}
	if (keycode == D)
	{
		data->player.key_D = false;
		printf("D released\n");
		printf("player x: %f\n", data->player.x);
		printf("player y: %f\n", data->player.y);
	}
	return (0);
}

void	move_player(t_data *data)
{
	float	step;

	step = 0.1;
	if (data->player.key_W)
		data->player.y -= step;
	if (data->player.key_S)
		data->player.y += step;
	if (data->player.key_A)
		data->player.x -= step;
	if (data->player.key_D)
		data->player.x += step;
}

int	draw_loop(t_data *data)
{
	move_player(data);
	draw_square(data, data->player.x, data->player.y, 0x00FF00, 10);
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
	// put_pixel(&data, 50, 50, 0x00FFFFFF);
	// draw_square(&data, WIDTH / 2, HEIGHT / 2, 0x00FF00, 10);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
}

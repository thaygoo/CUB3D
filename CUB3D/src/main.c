/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:55 by huburton          #+#    #+#             */
/*   Updated: 2026/02/19 14:56:55 by huburton         ###   ########.fr       */
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
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	ft_memset(data->tex, 0, sizeof(data->tex));
}

void	init_player(t_data *data)
{
	data->p.radius = 8;
	data->p.x = data->map.player_x * BLOCK + BLOCK / 2;
	data->p.y = data->map.player_y * BLOCK + BLOCK / 2;
	data->p.angle = PI * 1 / 3;
	data->p.step = 1;
	data->p.angle_speed = 2 * PI / 360;
	data->p.key_w = false;
	data->p.key_a = false;
	data->p.key_s = false;
	data->p.key_d = false;
	data->p.key_left = false;
	data->p.key_right = false;
	data->p.left = 0;
	data->p.right = 0;
	data->p.top = 0;
	data->p.bottom = 0;
	if (data->map.player_dir == 'N')
		data->p.angle = PI * 3 / 2;
	else if (data->map.player_dir == 'S')
		data->p.angle = PI * 1 / 2;
	else if (data->map.player_dir == 'E')
		data->p.angle = 0;
	else if (data->map.player_dir == 'W')
		data->p.angle = PI;
}

void	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	init_player(data);
	load_textures(data);
}

int	draw_loop(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bit_per_pixel,
			&data->size_line, &data->endian);
	move_player(data);
	cast_rays(data);
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
	init_game(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win_ptr, 17, 0, close_program, &data);
	mlx_loop_hook(data.mlx_ptr, draw_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

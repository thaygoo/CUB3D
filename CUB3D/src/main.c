/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:55 by huburton          #+#    #+#             */
/*   Updated: 2026/02/24 21:27:05 by msochor          ###   ########.fr       */
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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "Hello world!");
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
	
	
	mlx_loop(data.mlx_ptr);
	return (0);
}

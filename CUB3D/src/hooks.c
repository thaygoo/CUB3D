/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:16:20 by msochor           #+#    #+#             */
/*   Updated: 2026/03/12 21:24:04 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_program(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx_ptr, data->tex[i].img);
		i++;
	}
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_data(data);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_program(data);
	if (keycode == W)
		data->p.key_w = true;
	if (keycode == A)
		data->p.key_a = true;
	if (keycode == S)
		data->p.key_s = true;
	if (keycode == D)
		data->p.key_d = true;
	if (keycode == LEFT)
		data->p.key_left = true;
	if (keycode == RIGHT)
		data->p.key_right = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->p.key_w = false;
	if (keycode == A)
		data->p.key_a = false;
	if (keycode == S)
		data->p.key_s = false;
	if (keycode == D)
		data->p.key_d = false;
	if (keycode == LEFT)
		data->p.key_left = false;
	if (keycode == RIGHT)
		data->p.key_right = false;
	return (0);
}

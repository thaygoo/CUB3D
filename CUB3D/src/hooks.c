/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:16:20 by msochor           #+#    #+#             */
/*   Updated: 2026/02/26 19:24:12 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->p.key_W = true;
	if (keycode == A)
		data->p.key_A = true;
	if (keycode == S)
		data->p.key_S = true;
	if (keycode == D)
		data->p.key_D = true;
	if (keycode == LEFT)
		data->p.key_left = true;
	if (keycode == RIGHT)
		data->p.key_right = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->p.key_W = false;
	if (keycode == A)
		data->p.key_A = false;
	if (keycode == S)
		data->p.key_S = false;
	if (keycode == D)
		data->p.key_D = false;
	if (keycode == LEFT)
		data->p.key_left = false;
	if (keycode == RIGHT)
		data->p.key_right = false;
	return (0);
}

int	key_press_debug(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->p.key_W = true;
		printf("W pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == A)
	{
		data->p.key_A = true;
		printf("A pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == S)
	{
		data->p.key_S = true;
		printf("S pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == D)
	{
		data->p.key_D = true;
		printf("D pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == LEFT)
	{
		data->p.key_left = true;
		printf("LEFT pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == RIGHT)
	{
		data->p.key_right = true;
		printf("LEFT pressed\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	return (0);
}

int	key_release_debug(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->p.key_W = false;
		printf("W released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == A)
	{
		data->p.key_A = false;
		printf("A released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == S)
	{
		data->p.key_S = false;
		printf("S released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == D)
	{
		data->p.key_D = false;
		printf("D released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == LEFT)
	{
		data->p.key_left = false;
		printf("LEFT released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	if (keycode == RIGHT)
	{
		data->p.key_right = false;
		printf("LEFT released\n");
		printf("p x: %f\n", data->p.x);
		printf("p y: %f\n", data->p.y);
		printf("p ANGLE: %f\n", data->p.angle);
	}
	return (0);
}

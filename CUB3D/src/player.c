/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:43:00 by msochor           #+#    #+#             */
/*   Updated: 2026/03/06 15:26:41 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_w(t_data *data)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(data->p.angle);
	sin_angle = sin(data->p.angle);
	if (!touch(data->p.x + cos_angle * data->p.step,
			data->p.y + sin_angle * data->p.step, data))
	{
		data->p.x += cos_angle * data->p.step;
		data->p.y += sin_angle * data->p.step;
	}
}

void	move_s(t_data *data)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(data->p.angle);
	sin_angle = sin(data->p.angle);
	if (!touch(data->p.x - cos_angle * data->p.step,
			data->p.y - sin_angle * data->p.step, data))
	{
		data->p.x -= cos_angle * data->p.step;
		data->p.y -= sin_angle * data->p.step;
	}
}

void	move_a(t_data *data)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(data->p.angle);
	sin_angle = sin(data->p.angle);
	if (!touch(data->p.x + sin_angle * data->p.step,
			data->p.y - cos_angle * data->p.step, data))
	{
		data->p.x += sin_angle * data->p.step;
		data->p.y -= cos_angle * data->p.step;
	}
}

void	move_d(t_data *data)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(data->p.angle);
	sin_angle = sin(data->p.angle);
	if (!touch(data->p.x - sin_angle * data->p.step,
			data->p.y + cos_angle * data->p.step, data))
	{
		data->p.x -= sin_angle * data->p.step;
		data->p.y += cos_angle * data->p.step;
	}
}

void	move_player(t_data *data)
{
	if (data->p.key_left)
		data->p.angle -= data->p.angle_speed;
	if (data->p.key_right)
		data->p.angle += data->p.angle_speed;
	if (data->p.angle > 2 * PI)
		data->p.angle = 0;
	if (data->p.angle < 0)
		data->p.angle = 2 * PI;
	if (data->p.key_W)
		move_w(data);
	if (data->p.key_S)
		move_s(data);
	if (data->p.key_A)
		move_a(data);
	if (data->p.key_D)
		move_d(data);
}

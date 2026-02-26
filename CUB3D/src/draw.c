/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:59:01 by msochor           #+#    #+#             */
/*   Updated: 2026/02/26 20:21:22 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * data->size_line + x * data->bit_per_pixel / 8;
	data->addr[index] = color & 0xFF;
	data->addr[index + 1] = (color >> 8) & 0xFF;
	data->addr[index + 2] = (color >> 16) & 0xFF;
}

void	draw_circle(t_data *data, int cx, int cy, int r)
{
	double	step;
	double	angle;
	int		x;
	int		y;
	int		color;

	step = 0.01;
	angle = 0;
	color = 0x00FF00;
	while (angle < 2 * PI)
	{
		x = cx + (int)(r * cos(angle));
		y = cy + (int)(r * sin(angle));
		put_pixel(data, x, y, color);
		angle += step;
	}
}

void	draw_square(t_data *data, int x, int y, int size)
{
	int	i;
	int	color;

	color = 0xFFFFFF;
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

void	draw_map(t_data *data)
{
	char	**grid;
	int		x;
	int		y;

	grid = data->map.grid;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '1')
				draw_square(data, x * BLOCK, y * BLOCK, BLOCK);
			x++;
		}
		y++;
	}
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

// void	cast_ray(t_data *data)
// {
// 	float	ray_x;
// 	float	ray_y;
// 	float	cos_angle;
// 	float	sin_angle;

// 	ray_x = data->p.x;
// 	ray_y = data->p.y;
// 	cos_angle = cos(data->p.angle);
// 	sin_angle = sin(data->p.angle);
// 	while (!touch(ray_x, ray_y, data))
// 	{
// 		put_pixel(data, ray_x, ray_y, 0xFF0000);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// }

void	cast_ray(t_data *data)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	float	ray_w;
	
	ray_w = 2;
	float i = 0;
	
	
	while (i < ray_w)
	{
		ray_x = data->p.x;
		ray_y = data->p.y;
		cos_angle = cos(data->p.angle - i / PI);
		sin_angle = sin(data->p.angle - i / PI);
		while (!touch(ray_x, ray_y, data))
		{
			put_pixel(data, ray_x, ray_y, 0xFF0000);
			ray_x += cos_angle;
			ray_y += sin_angle;
		}
		i += 0.05;
	}
	i = 0;
	while (i < ray_w)
	{
		ray_x = data->p.x;
		ray_y = data->p.y;
		cos_angle = cos(data->p.angle + i / PI);
		sin_angle = sin(data->p.angle + i / PI);
		while (!touch(ray_x, ray_y, data))
		{
			put_pixel(data, ray_x, ray_y, 0x0000FF);
			ray_x += cos_angle;
			ray_y += sin_angle;
		}
		i += 0.05;
	}
}

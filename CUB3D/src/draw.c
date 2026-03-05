/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:59:01 by msochor           #+#    #+#             */
/*   Updated: 2026/03/05 15:33:17 by msochor          ###   ########.fr       */
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
	int	y;
	int	x;

	data->p.left = (int)((px - data->p.radius) / BLOCK);
	data->p.right = (int)((px + data->p.radius) / BLOCK);
	data->p.top = (int)((py - data->p.radius) / BLOCK);
	data->p.bottom = (int)((py + data->p.radius) / BLOCK);
	y = data->p.top;
	while (y <= data->p.bottom)
	{
		x = data->p.left;
		while (x <= data->p.right)
		{
			if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width
				|| data->map.grid[y][x] == '1')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

// void	draw_line(t_data *data, float x0, float y0,
//  float x1, float y1, int color)
// {
// 	float dx = x1 - x0;
// 	float dy = y1 - y0;

// 	float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

// 	float x_inc = dx / steps;
// 	float y_inc = dy / steps;

// 	float x = x0;
// 	float y = y0;

// 	int	i;
// 	i = 0;
// 	while (i <= steps)
// 	{
// 		put_pixel(data, (int)x, (int)y, color);
// 		x += x_inc;
// 		y += y_inc;
// 		i++;
// 	}
// }

void	draw_ray_line(t_data *data, float x1, float y1, int color)
{
	t_line	l;
	float	x;
	float	y;
	int		i;

	l.dx = x1 - data->p.x;
	l.dy = y1 - data->p.y;
	if (fabs(l.dx) > fabs(l.dy))
		l.steps = fabs(l.dx);
	else
		l.steps = fabs(l.dy);
	l.x_inc = l.dx / l.steps;
	l.y_inc = l.dy / l.steps;
	x = data->p.x;
	y = data->p.y;
	i = 0;
	while (i <= l.steps)
	{
		put_pixel(data, (int)x, (int)y, color);
		x += l.x_inc;
		y += l.y_inc;
		i++;
	}
}

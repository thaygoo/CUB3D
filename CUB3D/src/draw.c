/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:59:01 by msochor           #+#    #+#             */
/*   Updated: 2026/03/12 17:08:58 by msochor          ###   ########.fr       */
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
			if (y < 0 || y >= data->map.height
				|| x < 0 || x >= data->map.width
				|| data->map.grid[y][x] == '1')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

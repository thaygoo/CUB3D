/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:59:01 by msochor           #+#    #+#             */
/*   Updated: 2026/03/04 21:09:04 by msochor          ###   ########.fr       */
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

// bool	touch(float px, float py, t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = px / BLOCK;
// 	y = py / BLOCK;
// 	if (data->map.grid[y][x] == '1')
// 		return (true);
// 	return (false);
// }

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

// // touch check with radius around player position
// bool	touch(float px, float py, t_data *data)
// {
// 	int	left;
// 	int	right;
// 	int	top;
// 	int	bottom;

// 	left = (int)((px - data->p.radius) / BLOCK);
// 	right = (int)((px + data->p.radius) / BLOCK);
// 	top = (int)((py - data->p.radius) / BLOCK);
// 	bottom = (int)((py + data->p.radius) / BLOCK);
// 	for (int y = top; y <= bottom; y++)
// 	{
// 		for (int x = left; x <= right; x++)
// 		{
// 			// Treat out of bounds as wall
// 			if (y < 0 || y >= data->map.height
// 				|| x < 0 || x >= data->map.width)
// 				return true;
// 			if (data->map.grid[y][x] == '1')
// 				return true;
// 		}
// 	}
// 	return false;
// }

// bool    touch(float px, float py, t_data *data)
// {
// 	int left;
// 	int right;
// 	int top;
// 	int bottom;
// 	int y;
// 	int x;

// 	left = (int)((px - data->p.radius) / BLOCK);
// 	right = (int)((px + data->p.radius) / BLOCK);
// 	top = (int)((py - data->p.radius) / BLOCK);
// 	bottom = (int)((py + data->p.radius) / BLOCK);
// 	y = top;
// 	while (y <= bottom)
// 	{
// 		x = left;
// 		while (x <= right)
// 		{
// 			// Treat out of bounds as wall
// 			if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
// 				return true;
// 			if (data->map.grid[y][x] == '1')
// 				return true;
// 			x++;
// 		}
// 		y++;
// 	}
// 	return false;
// }
bool	touch(float px, float py, t_data *data)
{
	int	l;
	int	r;
	int	t;
	int	b;
	int	y;
	int	x;
	
	l = (int)((px - data->p.radius) / BLOCK);
	r = (int)((px + data->p.radius) / BLOCK);
	t = (int)((py - data->p.radius) / BLOCK);
	b = (int)((py + data->p.radius) / BLOCK);
	y = t;
	while (y <= b)
	{
		x = l;
		while (x <= r)
		{
			if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width
				|| data->map.grid[y][x] == '1')
				return true;
			x++;
		}
		y++;
	}
	return false;
}

static int	is_wall(t_data *data, int mapX, int mapY)
{
	if (mapY < 0 || mapY >= data->map.height
		|| mapX < 0 || mapX >= data->map.width)
		return (1); // treat outside map as wall
	return (data->map.grid[mapY][mapX] == '1');
}

void	cast_ray(t_data *data)
{
	// 1) Ray direction from player angle
	double rayDirX = cos(data->p.angle);
	double rayDirY = sin(data->p.angle);

	// 2) Player position in *map* coordinates (tile indices as doubles)
	double posX = data->p.x / (double)BLOCK;
	double posY = data->p.y / (double)BLOCK;

	// 3) Current square of the map the ray is in
	int	mapX = (int)posX;
	int	mapY = (int)posY;

	// 4) Length from one x-side to next x-side, same for y
	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

	// 5) Step direction in x & y and initial sideDist
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

	// 6) Perform DDA: walk cell by cell until we hit a wall or max steps
	int hit = 0;
	int side = 0; // 0 = x side, 1 = y side
	int maxSteps = 1000;

	while (!hit && maxSteps-- > 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (is_wall(data, mapX, mapY))
			hit = 1;
	}

	if (!hit)
		return ;

	// 7) Compute perpendicular distance to wall (for 3D later)
	double perpWallDist;
	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);

	// 8) Compute hit point in world (pixel) coordinates
	double hitX = data->p.x + rayDirX * perpWallDist * (double)BLOCK;
	double hitY = data->p.y + rayDirY * perpWallDist * (double)BLOCK;

	// 9) Draw ray from player to hit point on your 2D map
	// simple Bresenham-like interpolation
	int steps = (int)fmax(fabs(hitX - data->p.x), fabs(hitY - data->p.y));
	if (steps <= 0)
		return ;
	double dx = (hitX - data->p.x) / (double)steps;
	double dy = (hitY - data->p.y) / (double)steps;

	double x = data->p.x;
	double y = data->p.y;
	for (int i = 0; i <= steps; i++)
	{
		put_pixel(data, (int)x, (int)y, 0xFF0000);
		x += dx;
		y += dy;
	}
}

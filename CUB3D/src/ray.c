/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:04:35 by msochor           #+#    #+#             */
/*   Updated: 2026/03/05 15:26:16 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
RAY variables..............................
px, py -	player position converted to map grid space
dx, dy -	direction of the ray(angle from player starting position)
			if dx > 0, points right, else left
			if dy > 0, points down, else, up
mapX, mapY - map grid player position
stepX, stepY -	telling which direction to move to the next map grid
				according to dx,dy values:	-1 = left/up; +1 = right/down
sideDistX/sideDistY - distance from player to the first grid boundary
deltaDistX, deltaDistY - distance betweel vertical/horizontal lines
side - vertical/horizontal
hitX, hitY - position where day hits the wall
*/

void	init_ray_zero(t_ray *r)
{
	r->px = 0;
	r->py = 0;
	r->dx = 0;
	r->dy = 0;
	r->mapX = 0;
	r->mapY = 0;
	r->deltaDistX = 0;
	r->deltaDistY = 0;
	r->stepX = 0;
	r->stepY = 0;
	r->sideDistX = 0;
	r->sideDistY = 0;
	r->dist = 0;
	r->hitX = 0;
	r->hitY = 0;
	r->side = -1;
}

void	set_ray_one(t_ray *r, t_data *data)
{
	r->px = data->p.x / BLOCK;
	r->py = data->p.y / BLOCK;
	r->dx = cos(data->p.angle);
	r->dy = sin(data->p.angle);
	r->mapX = (int)r->px;
	r->mapY = (int)r->py;
	r->deltaDistX = fabs(1.0f / r->dx);
	r->deltaDistY = fabs(1.0f / r->dy);
}

void	set_ray_two(t_ray *r)
{
	if (r->dx < 0)
	{
		r->stepX = -1;
		r->sideDistX = (r->px - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - r->px) * r->deltaDistX;
	}
	if (r->dy < 0)
	{
		r->stepY = -1;
		r->sideDistY = (r->py - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - r->py) * r->deltaDistY;
	}
}

void	ray_init_set(t_ray *ray, t_data *data)
{
	init_ray_zero(ray);
	set_ray_one(ray, data);
	set_ray_two(ray);
}

void	ray_hitlookup(t_ray *r, t_data *data)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (data->map.grid[r->mapY][r->mapX] == '1')
			hit = 1;
	}
}

void	ray_cast(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->dist = ray->sideDistX - ray->deltaDistX;
	else
		ray->dist = ray->sideDistY - ray->deltaDistY;
	ray->hitX = data->p.x + ray->dx * ray->dist * BLOCK;
	ray->hitY = data->p.y + ray->dy * ray->dist * BLOCK;
	// draw_line(data, data->p.x, data->p.y, ray->hitX, ray->hitY, 0xFFFF00);
	draw_ray_line(data, ray->hitX, ray->hitY, 0xFFFF00);
}

void	cast_ray(t_data *data)
{
	t_ray	ray;

	ray_init_set(&ray, data);
	ray_hitlookup(&ray, data);
	ray_cast(&ray, data);
}

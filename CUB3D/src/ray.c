/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:04:35 by msochor           #+#    #+#             */
/*   Updated: 2026/03/12 20:54:13 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_ray_zero(t_ray *r)
{
	r->px = 0;
	r->py = 0;
	r->dx = 0;
	r->dy = 0;
	r->mapx = 0;
	r->mapy = 0;
	r->delta_dist_x = 0;
	r->delta_dist_y = 0;
	r->stepx = 0;
	r->stepy = 0;
	r->side_dist_x = 0;
	r->side_dist_y = 0;
	r->dist = 0;
	r->hit = 0;
	r->hitx = 0;
	r->hity = 0;
	r->side = -1;
	r->angle = 0;
}

static void	set_ray_one(t_ray *r, t_data *data, float angle)
{
	r->px = data->p.x / BLOCK;
	r->py = data->p.y / BLOCK;
	r->dx = cos(angle);
	r->dy = sin(angle);
	r->mapx = (int)r->px;
	r->mapy = (int)r->py;
	r->delta_dist_x = fabs(1.0f / r->dx);
	r->delta_dist_y = fabs(1.0f / r->dy);
	r->angle = angle;
}

static void	set_ray_two(t_ray *r)
{
	if (r->dx < 0)
	{
		r->stepx = -1;
		r->side_dist_x = (r->px - r->mapx) * r->delta_dist_x;
	}
	else
	{
		r->stepx = 1;
		r->side_dist_x = (r->mapx + 1.0 - r->px) * r->delta_dist_x;
	}
	if (r->dy < 0)
	{
		r->stepy = -1;
		r->side_dist_y = (r->py - r->mapy) * r->delta_dist_y;
	}
	else
	{
		r->stepy = 1;
		r->side_dist_y = (r->mapy + 1.0 - r->py) * r->delta_dist_y;
	}
}

static void	ray_hitlookup(t_ray *r, t_data *data)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (data->map.grid[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->dist = r->side_dist_x - r->delta_dist_x;
	else
		r->dist = r->side_dist_y - r->delta_dist_y;
	r->hitx = data->p.x + r->dx * r->dist * BLOCK;
	r->hity = data->p.y + r->dy * r->dist * BLOCK;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		num_rays;
	float	fov_step;
	float	start_angle;
	int		i;

	num_rays = 256;
	fov_step = (60.0f * (PI / 180.0f)) / num_rays;
	start_angle = data->p.angle - (30.0f * (PI / 180.0f));
	i = 0;
	while (i < num_rays)
	{
		init_ray_zero(&ray);
		set_ray_one(&ray, data, start_angle + i * fov_step);
		set_ray_two(&ray);
		ray_hitlookup(&ray, data);
		draw_3d_textures(data, &ray, i, num_rays);
		i++;
	}
}

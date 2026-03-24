/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:04:35 by msochor           #+#    #+#             */
/*   Updated: 2026/03/24 14:00:00 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	load_textures(t_data *data)
{
	data->tex[NORTH].img = mlx_xpm_file_to_image(
			data->mlx_ptr, data->map.no_texture, &data->tex[NORTH].w,
			&data->tex[NORTH].h);
	data->tex[NORTH].addr = mlx_get_data_addr(
			data->tex[NORTH].img, &data->tex[NORTH].bpp,
			&data->tex[NORTH].line_len, &data->tex[NORTH].endian);
	data->tex[SOUTH].img = mlx_xpm_file_to_image(
			data->mlx_ptr, data->map.so_texture, &data->tex[SOUTH].w,
			&data->tex[SOUTH].h);
	data->tex[SOUTH].addr = mlx_get_data_addr(
			data->tex[SOUTH].img, &data->tex[SOUTH].bpp,
			&data->tex[SOUTH].line_len, &data->tex[SOUTH].endian);
	data->tex[WEST].img = mlx_xpm_file_to_image(
			data->mlx_ptr, data->map.we_texture, &data->tex[WEST].w,
			&data->tex[WEST].h);
	data->tex[WEST].addr = mlx_get_data_addr(
			data->tex[WEST].img, &data->tex[WEST].bpp,
			&data->tex[WEST].line_len, &data->tex[WEST].endian);
	data->tex[EAST].img = mlx_xpm_file_to_image(
			data->mlx_ptr, data->map.ea_texture, &data->tex[EAST].w,
			&data->tex[EAST].h);
	data->tex[EAST].addr = mlx_get_data_addr(
			data->tex[EAST].img, &data->tex[EAST].bpp,
			&data->tex[EAST].line_len, &data->tex[EAST].endian);
}

static void	draw_3d_setup(t_data *data, t_ray *ray, t_texture_sample *t)
{
	t->perp_dist = ray->dist * cos(ray->angle - data->p.angle);
	if (t->perp_dist < 0.0001f)
		t->perp_dist = 0.0001f;
	t->line_height = (int)(HEIGHT / t->perp_dist);
	t->start = (HEIGHT / 2) - (t->line_height / 2);
	t->end = (HEIGHT / 2) + (t->line_height / 2);
	if (t->start < 0)
		t->start = 0;
	if (t->end >= HEIGHT)
		t->end = HEIGHT - 1;
	t->ceil_color = (data->map.ceiling_color[0] << 16)
		| (data->map.ceiling_color[1] << 8)
		| data->map.ceiling_color[2];
	t->floor_color = (data->map.floor_color[0] << 16)
		| (data->map.floor_color[1] << 8)
		| data->map.floor_color[2];
}

static void	draw_3d_setup_two(t_data *data, t_ray *ray, t_texture_sample *t)
{
	if (ray->side == 0 && ray->dx > 0)
		t->tex_id = EAST;
	else if (ray->side == 0)
		t->tex_id = WEST;
	else if (ray->dy > 0)
		t->tex_id = SOUTH;
	else
		t->tex_id = NORTH;
	if (ray->side == 0)
		t->wall_x = ray->hity / BLOCK;
	else
		t->wall_x = ray->hitx / BLOCK;
	t->wall_x -= floor(t->wall_x);
	t->tex_x = (int)(t->wall_x * data->tex[t->tex_id].w);
	if ((ray->side == 0 && ray->dx < 0)
		|| (ray->side == 1 && ray->dy > 0))
		t->tex_x = data->tex[t->tex_id].w - t->tex_x - 1;
	t->tex_start = 0;
	if (t->line_height > HEIGHT)
		t->tex_start = (t->line_height - HEIGHT) / 2;
}

static int	get_wall_color(t_data *data, t_texture_sample *t, int y)
{
	int		d;
	int		tex_y;
	char	*pixel;

	d = (y - t->start + t->tex_start) * 256;
	tex_y = ((d * data->tex[t->tex_id].h) / t->line_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= data->tex[t->tex_id].h)
		tex_y = data->tex[t->tex_id].h - 1;
	pixel = data->tex[t->tex_id].addr
		+ tex_y * data->tex[t->tex_id].line_len
		+ t->tex_x * (data->tex[t->tex_id].bpp / 8);
	return (*(unsigned int *)pixel);
}

void	draw_3d_textures(t_data *data, t_ray *ray, int i, int num_rays)
{
	t_texture_sample	t;
	int					y;
	int					w;
	int					color;

	t.slice_width = (float)WIDTH / num_rays;
	t.screen_x = (int)(i * t.slice_width);
	draw_3d_setup(data, ray, &t);
	draw_3d_setup_two(data, ray, &t);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < t.start)
			color = t.ceil_color;
		else if (y <= t.end)
			color = get_wall_color(data, &t, y);
		else
			color = t.floor_color;
		w = -1;
		while (++w < (int)t.slice_width)
			put_pixel(data, t.screen_x + w, y, color);
	}
}

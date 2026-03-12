/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:04:35 by msochor           #+#    #+#             */
/*   Updated: 2026/03/12 19:47:30 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
RAY variables..............................
px, py -	player position converted to map grid space
dx, dy -	direction of the ray(angle from player starting position)
			if dx > 0, points right, else left
			if dy > 0, points down, else, up
mapx, mapy - map grid player position
stepx, stepy -	telling which direction to move to the next map grid
				according to dx,dy values:	-1 = left/up; +1 = right/down
side_dist_x/side_dist_y - distance from player to the first grid boundary
delta_dist_x, delta_dist_y - distance betweel vertical/horizontal lines
side - vertical/horizontal
hitx, hity - position where day hits the wall
*/

void	init_ray_zero(t_ray *r)
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

void	set_ray_one(t_ray *r, t_data *data, float angle)
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

void	set_ray_two(t_ray *r)
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

void	ray_init_set(t_ray *ray, t_data *data, float angle)
{
	init_ray_zero(ray);
	set_ray_one(ray, data, angle);
	set_ray_two(ray);
}

void	ray_hitlookup(t_ray *r, t_data *data)
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

// // cast rays in 2d debug area
// void	draw_2d_ray(t_ray *ray, t_data *data, int color)
// {
// 	if (ray->side == 0)
// 		ray->dist = ray->side_dist_x - ray->delta_dist_x;
// 	else
// 		ray->dist = ray->side_dist_y - ray->delta_dist_y;
// 	ray->hitx = data->p.x + ray->dx * ray->dist * BLOCK;
// 	ray->hity = data->p.y + ray->dy * ray->dist * BLOCK;
// 	draw_ray_line(data, ray->hitx, ray->hity, color);
// }

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

/*
int viewWidth - width of the 3D view 
float slice_width - how wide each vertical slice is
int screen_x - x-position of this slice on screen
int line_height - compute wall height 
int start, end  - top, bottom of the wall slice
int tex_id - marks what texture to use(N,S,E,W)
wall_x
tex_x - texture column
tex_y - texture row
*/


typedef	struct	s_texture_sample
{
	float	slice_width;
	int		screen_x;
	float	perp_dist;
	int		line_height;
	int		start;
	int		end;
	int		ceil_color;
	int		floor_color;
	int		tex_id;
	float	wall_x;
	int		tex_x;
	int		tex_y;
	int		tex_start;
	char	*pixel;
	int		color;
}	t_texture_sample;

void	draw_3d_setup(t_data *data, t_ray *ray, t_texture_sample *t)
{
	t->perp_dist = ray->dist * cos(ray->angle - data->p.angle);
	if (t->perp_dist < 0.0001f)
		t->perp_dist = 0.0001f;
	t->line_height = (int)(HEIGHT / t->perp_dist);
	t->start = (HEIGHT / 2) - (t->line_height / 2);
	t->end   = (HEIGHT / 2) + (t->line_height / 2);
	// clamping to not going out of bounds
	if (t->start < 0) 
		t->start = 0;
	if (t->end >= HEIGHT) 
		t->end = HEIGHT - 1;
	t->ceil_color = (data->map.ceiling_color[0] << 16)
				  | (data->map.ceiling_color[1] << 8)
				  |  data->map.ceiling_color[2];
	t->floor_color = (data->map.floor_color[0] << 16)
				   | (data->map.floor_color[1] << 8)
				   |  data->map.floor_color[2];
}
void	draw_3d_textures(t_data *data, t_ray *ray, int i, int numRays)
{
	t_texture_sample t;

	t.slice_width = (float)WIDTH / numRays;
	t.screen_x = (int)(i * t.slice_width);
	draw_3d_setup(data, ray, &t);
	


	// draw ceiling
	for (int y = 0; y < t.start; y++)
		for (int w = 0; w < t.slice_width; w++)
			put_pixel(data, t.screen_x + w, y, t.ceil_color);

	// --- TEXTURED WALL STARTS HERE ---

	// choose texture
	if (ray->side == 0)
		t.tex_id = (ray->dx > 0) ? EAST : WEST;
	else
		t.tex_id = (ray->dy > 0) ? SOUTH : NORTH;

	// compute texture X coordinate
	if (ray->side == 0)
		t.wall_x = ray->hity / BLOCK;   // vertical wall → use Y
	else
		t.wall_x = ray->hitx / BLOCK;   // horizontal wall → use X
	t.wall_x -= floor(t.wall_x);

	t.tex_x = (int)(t.wall_x * data->tex[t.tex_id].w);

	// flip if needed
	if ((ray->side == 0 && ray->dx < 0) ||
		(ray->side == 1 && ray->dy > 0))
		t.tex_x = data->tex[t.tex_id].w - t.tex_x - 1;
	
	// handles very tall walls(linehight > HEIGHT) when player is close to the wall
	t.tex_start = 0;
	if (t.line_height > HEIGHT)
		t.tex_start = (t.line_height - HEIGHT) / 2;
	
	// draw textured wall
	for (int y = t.start; y < t.end; y++)
	{
		int d = (y - t.start + t.tex_start) * 256;
		t.tex_y = ((d * data->tex[t.tex_id].h) / t.line_height) / 256;
	
		if (t.tex_y < 0) t.tex_y = 0;
		if (t.tex_y >= data->tex[t.tex_id].h) t.tex_y = data->tex[t.tex_id].h - 1;

		t.pixel = data->tex[t.tex_id].addr
			+ t.tex_y * data->tex[t.tex_id].line_len
			+ t.tex_x * (data->tex[t.tex_id].bpp / 8);

		t.color = *(unsigned int *)t.pixel;

		for (int w = 0; w < t.slice_width; w++)
			put_pixel(data, t.screen_x + w, y, t.color);
	}
	// --- TEXTURED WALL ENDS HERE ---

	// draw floor
	for (int y = t.end; y < HEIGHT; y++)
		for (int w = 0; w < t.slice_width; w++)
			put_pixel(data, t.screen_x + w, y, t.floor_color);
}

void cast_rays(t_data *data)
{
	t_ray	ray;
	int		numRays = 256;
	float	fovRad = 60 * (PI / 180.0f);
	float	angleStep = fovRad / numRays;
	float	startAngle = data->p.angle - (fovRad / 2);

	for (int i = 0; i < numRays; i++)
	{
		float rayAngle = startAngle + i * angleStep;

		ray_init_set(&ray, data, rayAngle);
		ray_hitlookup(&ray, data);
		draw_3d_textures(data, &ray, i, numRays);
	}
}


// backup before slicinggggg
// void	draw_3d_textures(t_data *data, t_ray *ray, int i, int numRays)
// {
// 	t_texture_sample t;

// 	t.slice_width = (float)WIDTH / numRays;
// 	t.screen_x = (int)(i * t.slice_width);

	
// 	t.perp_dist = ray->dist * cos(ray->angle - data->p.angle);
// 	if (t.perp_dist < 0.0001f)
// 		t.perp_dist = 0.0001f;
// 	t.line_height = (int)(HEIGHT / t.perp_dist);
// 	t.start = (HEIGHT / 2) - (t.line_height / 2);
// 	t.end   = (HEIGHT / 2) + (t.line_height / 2);
// 	// clamping to not going out of bounds
// 	if (t.start < 0) t.start = 0;
// 	if (t.end >= HEIGHT) t.end = HEIGHT - 1;

// 	t.ceil_color = (data->map.ceiling_color[0] << 16)
// 				  | (data->map.ceiling_color[1] << 8)
// 				  |  data->map.ceiling_color[2];

// 	t.floor_color = (data->map.floor_color[0] << 16)
// 				   | (data->map.floor_color[1] << 8)
// 				   |  data->map.floor_color[2];

// 	// draw ceiling
// 	for (int y = 0; y < t.start; y++)
// 		for (int w = 0; w < t.slice_width; w++)
// 			put_pixel(data, t.screen_x + w, y, t.ceil_color);

// 	// --- TEXTURED WALL STARTS HERE ---

// 	// choose texture
// 	if (ray->side == 0)
// 		t.tex_id = (ray->dx > 0) ? EAST : WEST;
// 	else
// 		t.tex_id = (ray->dy > 0) ? SOUTH : NORTH;

// 	// compute texture X coordinate
// 	if (ray->side == 0)
// 		t.wall_x = ray->hity / BLOCK;   // vertical wall → use Y
// 	else
// 		t.wall_x = ray->hitx / BLOCK;   // horizontal wall → use X
// 	t.wall_x -= floor(t.wall_x);

// 	t.tex_x = (int)(t.wall_x * data->tex[t.tex_id].w);

// 	// flip if needed
// 	if ((ray->side == 0 && ray->dx < 0) ||
// 		(ray->side == 1 && ray->dy > 0))
// 		t.tex_x = data->tex[t.tex_id].w - t.tex_x - 1;
	
// 	// handles very tall walls(linehight > HEIGHT) when player is close to the wall
// 	t.tex_start = 0;
// 	if (t.line_height > HEIGHT)
// 		t.tex_start = (t.line_height - HEIGHT) / 2;
	
// 	// draw textured wall
// 	for (int y = t.start; y < t.end; y++)
// 	{
// 		int d = (y - t.start + t.tex_start) * 256;
// 		t.tex_y = ((d * data->tex[t.tex_id].h) / t.line_height) / 256;
	
// 		if (t.tex_y < 0) t.tex_y = 0;
// 		if (t.tex_y >= data->tex[t.tex_id].h) t.tex_y = data->tex[t.tex_id].h - 1;

// 		t.pixel = data->tex[t.tex_id].addr
// 			+ t.tex_y * data->tex[t.tex_id].line_len
// 			+ t.tex_x * (data->tex[t.tex_id].bpp / 8);

// 		t.color = *(unsigned int *)t.pixel;

// 		for (int w = 0; w < t.slice_width; w++)
// 			put_pixel(data, t.screen_x + w, y, t.color);
// 	}
// 	// --- TEXTURED WALL ENDS HERE ---

// 	// draw floor
// 	for (int y = t.end; y < HEIGHT; y++)
// 		for (int w = 0; w < t.slice_width; w++)
// 			put_pixel(data, t.screen_x + w, y, t.floor_color);
// }
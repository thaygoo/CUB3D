/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:04:35 by msochor           #+#    #+#             */
/*   Updated: 2026/03/12 15:46:53 by msochor          ###   ########.fr       */
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
	r->angle = 0;
}

void	set_ray_one(t_ray *r, t_data *data, float angle)
{
	r->px = data->p.x / BLOCK;
	r->py = data->p.y / BLOCK;
	r->dx = cos(angle);
	r->dy = sin(angle);
	r->mapX = (int)r->px;
	r->mapY = (int)r->py;
	r->deltaDistX = fabs(1.0f / r->dx);
	r->deltaDistY = fabs(1.0f / r->dy);
	r->angle = angle;
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

void	ray_init_set(t_ray *ray, t_data *data, float angle)
{
	init_ray_zero(ray);
	set_ray_one(ray, data, angle);
	set_ray_two(ray);
}

// void	ray_hitlookup(t_ray *r, t_data *data)
// {
// 	int	hit;

// 	hit = 0;
// 	while (!hit)
// 	{
// 		if (r->sideDistX < r->sideDistY)
// 		{
// 			r->sideDistX += r->deltaDistX;
// 			r->mapX += r->stepX;
// 			r->side = 0;
// 		}
// 		else
// 		{
// 			r->sideDistY += r->deltaDistY;
// 			r->mapY += r->stepY;
// 			r->side = 1;
// 		}
// 		if (data->map.grid[r->mapY][r->mapX] == '1')
// 			hit = 1;
// 	}
// }

void ray_hitlookup(t_ray *r, t_data *data)
{
	int hit = 0;

	while (!hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0; // vertical wall
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1; // horizontal wall
		}

		if (data->map.grid[r->mapY][r->mapX] == '1')
			hit = 1;
	}

	// --- EXACT WALL DISTANCE (fixes close‑range wobble) ---
	if (r->side == 0)
		r->dist = (r->mapX - r->px + (1 - r->stepX) / 2.0f) / r->dx;
	else
		r->dist = (r->mapY - r->py + (1 - r->stepY) / 2.0f) / r->dy;

	// --- EXACT HIT POINT IN PIXELS ---
	r->hitX = (r->px + r->dx * r->dist) * BLOCK;
	r->hitY = (r->py + r->dy * r->dist) * BLOCK;
}

// cast rays in 2d map area
void	draw_2d_ray(t_ray *ray, t_data *data, int color)
{
	if (ray->side == 0)
		ray->dist = ray->sideDistX - ray->deltaDistX;
	else
		ray->dist = ray->sideDistY - ray->deltaDistY;
	ray->hitX = data->p.x + ray->dx * ray->dist * BLOCK;
	ray->hitY = data->p.y + ray->dy * ray->dist * BLOCK;

	draw_ray_line(data, ray->hitX, ray->hitY, color);
}

// void	cast_ray(t_data *data, float angle, int color)
// {
// 	t_ray	ray;

// 	ray_init_set(&ray, data, angle);
// 	ray_hitlookup(&ray, data);
// 	ray_cast(&ray, data, color);
// }

// void	cast_rays(t_data *data, int fov)
// {
// 	int	i;

// 	cast_ray(data, data->p.angle, 0xFFFF00);
// 	i = 1;
// 	while (i <= fov / 2)
// 	{
// 		cast_ray(data, data->p.angle + i * data->p.angle_speed, 0xFF0000);
// 		i++;
// 	}
// 	i = 1;
// 	while (i <= fov / 2)
// 	{
// 		cast_ray(data, data->p.angle - i * data->p.angle_speed, 0xFF0000);
// 		i++;
// 	}
// }


/*
int viewWidth - width of the 3D view (half of the window)

float sliceWidth - how wide each vertical slice is

int screenX - x-position of this slice on screen

int lineHeight - compute wall height (simple version)

int start, end center the wall vertically
*/
void draw_3d_slice(t_data *data, t_ray *ray, int i, int numRays)
{
	// int viewWidth = WIDTH / 2;
	int viewWidth = WIDTH / 2;
	float sliceWidth = (float)viewWidth / numRays;

	int screenX = (int)(i * sliceWidth) + viewWidth;
	// int screenX = (int)(i * sliceWidth) + 0;

	// int lineHeight = (int)(HEIGHT / ray->dist);  //fisheyed
	float correctedDist = ray->dist * cos(ray->angle - data->p.angle);
	int lineHeight = (int)(HEIGHT / correctedDist);



	int start = (HEIGHT / 2) - (lineHeight / 2);
	int end   = (HEIGHT / 2) + (lineHeight / 2);

	if (start < 0) start = 0;
	if (end >= HEIGHT) end = HEIGHT - 1;

	int ceilColor = (data->map.ceiling_color[0] << 16)
				  | (data->map.ceiling_color[1] << 8)
				  |  data->map.ceiling_color[2];

	int floorColor = (data->map.floor_color[0] << 16)
				   | (data->map.floor_color[1] << 8)
				   |  data->map.floor_color[2];

	for (int y = 0; y < start; y++)
		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, ceilColor);

	int wallBright = 0xFFFFFF;
	int wallDark   = 0xAAAAAA;
	int wallColor  = (ray->side == 0) ? wallBright : wallDark;

	for (int y = start; y < end; y++)
		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, wallColor);

	for (int y = end; y < HEIGHT; y++)
		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, floorColor);
}

void load_textures(t_data *data)
{
	data->tex[NORTH].img = mlx_xpm_file_to_image(
		data->mlx_ptr, data->map.no_texture, &data->tex[NORTH].w, &data->tex[NORTH].h);
	data->tex[NORTH].addr = mlx_get_data_addr(
		data->tex[NORTH].img, &data->tex[NORTH].bpp,
		&data->tex[NORTH].line_len, &data->tex[NORTH].endian);
	data->tex[SOUTH].img = mlx_xpm_file_to_image(
		data->mlx_ptr, data->map.so_texture, &data->tex[SOUTH].w, &data->tex[SOUTH].h);
	data->tex[SOUTH].addr = mlx_get_data_addr(
		data->tex[SOUTH].img, &data->tex[SOUTH].bpp,
		&data->tex[SOUTH].line_len, &data->tex[SOUTH].endian);
	data->tex[WEST].img = mlx_xpm_file_to_image(
		data->mlx_ptr, data->map.we_texture, &data->tex[WEST].w, &data->tex[WEST].h);
	data->tex[WEST].addr = mlx_get_data_addr(
		data->tex[WEST].img, &data->tex[WEST].bpp,
		&data->tex[WEST].line_len, &data->tex[WEST].endian);
	data->tex[EAST].img = mlx_xpm_file_to_image(
		data->mlx_ptr, data->map.ea_texture, &data->tex[EAST].w, &data->tex[EAST].h);
	data->tex[EAST].addr = mlx_get_data_addr(
		data->tex[EAST].img, &data->tex[EAST].bpp,
		&data->tex[EAST].line_len, &data->tex[EAST].endian);
}

void draw_3d_textures(t_data *data, t_ray *ray, int i, int numRays)
{
	int viewWidth = WIDTH / 2;
	// float sliceWidth = (float)viewWidth / numRays;
	int sliceWidth = viewWidth / numRays;

	int screenX = (int)(i * sliceWidth) + viewWidth;

	float perpDist = ray->dist * cos(ray->angle - data->p.angle);
	if (perpDist < 0.0001f)
		perpDist = 0.0001f;
	int lineHeight = (int)(HEIGHT / perpDist);
	
	int start = (HEIGHT / 2) - (lineHeight / 2);
	int end   = (HEIGHT / 2) + (lineHeight / 2);

	if (start < 0) start = 0;
	if (end >= HEIGHT) end = HEIGHT - 1;

	int ceilColor = (data->map.ceiling_color[0] << 16)
				  | (data->map.ceiling_color[1] << 8)
				  |  data->map.ceiling_color[2];

	int floorColor = (data->map.floor_color[0] << 16)
				   | (data->map.floor_color[1] << 8)
				   |  data->map.floor_color[2];

	// draw ceiling
	for (int y = 0; y < start; y++)
		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, ceilColor);

	// --- TEXTURED WALL STARTS HERE ---

	// choose texture
	int tex_id;
	if (ray->side == 0)
		tex_id = (ray->dx > 0) ? EAST : WEST;
	else
		tex_id = (ray->dy > 0) ? SOUTH : NORTH;

	// compute texture X coordinate
	float wallX;

	if (ray->side == 0)
		wallX = ray->hitY / BLOCK;   // vertical wall → use Y
	else
		wallX = ray->hitX / BLOCK;   // horizontal wall → use X

	wallX -= floor(wallX);

	int texX = (int)(wallX * data->tex[tex_id].w);

	// flip if needed
	if ((ray->side == 0 && ray->dx < 0) ||
		(ray->side == 1 && ray->dy > 0))
		texX = data->tex[tex_id].w - texX - 1;
	
	int texStart = 0;
	if (lineHeight > HEIGHT)
		texStart = (lineHeight - HEIGHT) / 2;
	
		// draw textured wall
	for (int y = start; y < end; y++)
	{
		int d = (y - start + texStart) * 256;
		int texY = ((d * data->tex[tex_id].h) / lineHeight) / 256;

		if (texY < 0) texY = 0;
		if (texY >= data->tex[tex_id].h) texY = data->tex[tex_id].h - 1;

		char *pixel = data->tex[tex_id].addr
			+ texY * data->tex[tex_id].line_len
			+ texX * (data->tex[tex_id].bpp / 8);

		int color = *(unsigned int *)pixel;

		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, color);
	}
	// --- TEXTURED WALL ENDS HERE ---

	// draw floor
	for (int y = end; y < HEIGHT; y++)
		for (int w = 0; w < sliceWidth; w++)
			put_pixel(data, screenX + w, y, floorColor);
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

		draw_2d_ray(&ray, data, 0xFF0000);
		// draw_3d_slice(data, &ray, i, numRays);
		draw_3d_textures(data, &ray, i, numRays);
	}
}

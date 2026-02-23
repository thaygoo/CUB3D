/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:04 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:43:04 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	process_map_line(char *line, t_data *data, int *map_ended)
{
	int	j;
	int	len;

	j = 0;
	while (is_whitespace(line[j]))
		j++;
	if (line[j] != '\0')
	{
		if (*map_ended)
			return (1);
		len = ft_strlen(line);
		if (len > data->map.width)
			data->map.width = len;
		data->map.height++;
	}
	else if (data->map.height > 0)
		*map_ended = 1;
	return (0);
}

static int	get_map_dimensions(char **lines, int start_idx, t_data *data)
{
	int	i;
	int	map_ended;

	data->map.height = 0;
	data->map.width = 0;
	i = start_idx;
	map_ended = 0;
	while (lines[i])
	{
		if (process_map_line(lines[i], data, &map_ended))
			return (1);
		i++;
	}
	if (data->map.height == 0 || data->map.width == 0)
		return (1);
	return (0);
}

static int	allocate_grid(t_data *data)
{
	int	i;

	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		return (1);
	i = 0;
	while (i < data->map.height)
	{
		data->map.grid[i] = malloc(sizeof(char) * (data->map.width + 1));
		if (!data->map.grid[i])
			return (1);
		i++;
	}
	data->map.grid[data->map.height] = NULL;
	return (0);
}

static void	fill_grid(char **lines, int start_idx, t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		len = ft_strlen(lines[start_idx + i]);
		while (j < data->map.width)
		{
			if (j < len)
				data->map.grid[i][j] = lines[start_idx + i][j];
			else
				data->map.grid[i][j] = ' ';
			j++;
		}
		data->map.grid[i][data->map.width] = '\0';
		i++;
	}
}

int	extract_grid(char **lines, t_data *data, int start_idx)
{
	int	j;

	while (lines[start_idx])
	{
		j = 0;
		while (is_whitespace(lines[start_idx][j]))
			j++;
		if (lines[start_idx][j] != '\0')
			break ;
		start_idx++;
	}
	if (get_map_dimensions(lines, start_idx, data) != 0)
		return (1);
	if (allocate_grid(data) != 0)
		return (1);
	fill_grid(lines, start_idx, data);
	if (find_player(data) != 0)
		return (1);
	return (0);
}

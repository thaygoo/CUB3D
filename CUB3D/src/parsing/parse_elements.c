/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:42:59 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:42:59 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_color_component(char *line, int *i, int *val)
{
	*val = ft_atoi(&line[*i]);
	if (*val < 0 || *val > 255)
		return (1);
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	return (0);
}

static int	parse_color(char *line, int color[3])
{
	int	i;
	int	j;

	i = 1;
	while (is_whitespace(line[i]))
		i++;
	j = 0;
	while (j < 3)
	{
		if (parse_color_component(line, &i, &color[j]))
			return (1);
		if (j < 2)
		{
			while (is_whitespace(line[i]))
				i++;
			if (line[i] != ',')
				return (1);
			i++;
			while (is_whitespace(line[i]))
				i++;
		}
		j++;
	}
	return (0);
}

static int	parse_texture(char *line, char **texture)
{
	int	i;
	int	j;

	i = 2;
	while (is_whitespace(line[i]))
		i++;
	if (*texture)
		return (1);
	j = i;
	while (line[j] && !is_whitespace(line[j]))
		j++;
	*texture = malloc(sizeof(char) * (j - i + 1));
	if (!*texture)
		return (1);
	j = 0;
	while (line[i] && !is_whitespace(line[i]))
	{
		(*texture)[j] = line[i];
		i++;
		j++;
	}
	(*texture)[j] = '\0';
	return (0);
}

static int	try_parse_element(char *line, t_data *data, int *found)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		*found += (parse_texture(line, &data->map.no_texture) == 0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		*found += (parse_texture(line, &data->map.so_texture) == 0);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		*found += (parse_texture(line, &data->map.we_texture) == 0);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		*found += (parse_texture(line, &data->map.ea_texture) == 0);
	else if (ft_strncmp(line, "F ", 2) == 0)
		*found += (parse_color(line, data->map.floor_color) == 0);
	else if (ft_strncmp(line, "C ", 2) == 0)
		*found += (parse_color(line, data->map.ceiling_color) == 0);
	else
		return (1);
	return (0);
}

int	extract_elements(char **lines, t_data *data, int *map_start_idx)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (lines[i] && found < 6)
	{
		j = 0;
		while (is_whitespace(lines[i][j]))
			j++;
		if (lines[i][j] == '\0')
		{
			i++;
			continue ;
		}
		if (try_parse_element(&lines[i][j], data, &found))
			return (1);
		i++;
	}
	if (found != 6)
		return (1);
	*map_start_idx = i;
	return (0);
}

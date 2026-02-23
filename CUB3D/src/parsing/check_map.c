/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:42:44 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:42:44 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_valid_neighbor(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
		return (0);
	if (data->map.grid[y][x] == ' ')
		return (0);
	return (1);
}

static int	check_cell(t_data *data, int y, int x)
{
	char	c;

	c = data->map.grid[y][x];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!is_valid_neighbor(data, y - 1, x))
			return (1);
		if (!is_valid_neighbor(data, y + 1, x))
			return (1);
		if (!is_valid_neighbor(data, y, x - 1))
			return (1);
		if (!is_valid_neighbor(data, y, x + 1))
			return (1);
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (check_cell(data, i, j) != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

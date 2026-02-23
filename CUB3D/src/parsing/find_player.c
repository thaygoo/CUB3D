/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:42:53 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:42:53 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	validate_player_cell(t_data *data, int i, int j, int *p_count)
{
	if (data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S'
		|| data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W')
	{
		data->map.player_x = j;
		data->map.player_y = i;
		data->map.player_dir = data->map.grid[i][j];
		(*p_count)++;
	}
}

int	find_player(t_data *data)
{
	int	i;
	int	j;
	int	p_count;

	p_count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			validate_player_cell(data, i, j, &p_count);
			if (data->map.grid[i][j] != '0' && data->map.grid[i][j] != '1'
				&& !is_whitespace(data->map.grid[i][j])
				&& data->map.grid[i][j] != data->map.player_dir)
				return (1);
			j++;
		}
		i++;
	}
	if (p_count != 1)
		return (1);
	return (0);
}

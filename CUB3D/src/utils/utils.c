/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msochor <msochor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:20 by huburton          #+#    #+#             */
/*   Updated: 2026/04/01 18:20:31 by msochor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_data(t_data *data)
{
	free_split(data->map.grid);
	if (data->map.no_texture)
		free(data->map.no_texture);
	if (data->map.so_texture)
		free(data->map.so_texture);
	if (data->map.we_texture)
		free(data->map.we_texture);
	if (data->map.ea_texture)
		free(data->map.ea_texture);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	free_texture_names(t_data *data)
{
	int	i;

	i = 0;
	free(data->map.no_texture);
	free(data->map.so_texture);
	free(data->map.we_texture);
	free(data->map.ea_texture);
	if (data->map.grid)
	{
		while (i < data->map.height)
		{
			free(data->map.grid[i]);
			i++;
		}
		free(data->map.grid);
	}
}

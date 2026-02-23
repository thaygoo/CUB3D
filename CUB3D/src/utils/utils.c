/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:20 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:43:20 by huburton         ###   ########.fr       */
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

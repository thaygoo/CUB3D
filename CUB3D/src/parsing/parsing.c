/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:09 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:43:09 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4 || filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		return (1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D map.cub>\n", 2);
		return (1);
	}
	if (check_extension(argv[1]) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension, must be .cub\n", 2);
		return (1);
	}
	return (0);
}

static int	check_parse_step(int result, void *lines_ptr, char *err_msg)
{
	char	**lines;

	if (result != 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err_msg, 2);
		ft_putstr_fd("\n", 2);
		if (lines_ptr)
		{
			lines = (char **)lines_ptr;
			free_split(lines);
		}
		return (1);
	}
	return (0);
}

int	parse_map(char *filename, t_data *data)
{
	char	**lines;
	int		map_start_idx;

	lines = read_file_lines(filename);
	if (!lines)
	{
		ft_putstr_fd("Error\nCannot read file\n", 2);
		return (1);
	}
	if (check_parse_step(extract_elements(lines, data, &map_start_idx),
			lines, "Invalid elements in map file"))
		return (1);
	if (check_parse_step(extract_grid(lines, data, map_start_idx),
			lines, "Invalid map grid"))
		return (1);
	if (check_parse_step(validate_map(data),
			lines, "Map is not closed or invalid"))
		return (1);
	free_split(lines);
	return (0);
}

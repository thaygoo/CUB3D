/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:57:04 by huburton          #+#    #+#             */
/*   Updated: 2026/02/19 14:57:04 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
}

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

int	parse_map(char *filename, t_data *data)
{
	int	fd;

	(void)data;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCannot open file");
		return (1);
	}
	// TODO: Lire le fichier avec get_next_line
	// TODO: Parser les textures (NO, SO, WE, EA)
	// TODO: Parser les couleurs (F, C)
	// TODO: Parser la map (1, 0, N, S, E, W)
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:00:00 by huburton          #+#    #+#             */
/*   Updated: 2026/02/19 12:00:00 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_data
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

// Parsing
int		check_args(int argc, char **argv);
int		parse_map(char *filename, t_data *data);

// Utils
void	free_data(t_data *data);
void	ft_putstr_fd(char *s, int fd);

#endif

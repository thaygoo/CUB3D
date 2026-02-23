/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:41 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:43:41 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

typedef struct s_map
{
	char	**grid;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_data
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int		check_args(int argc, char **argv);
int		check_extension(char *filename);
int		parse_map(char *filename, t_data *data);
char	**read_file_lines(char *filename);
int		extract_elements(char **lines, t_data *data, int *map_start_idx);
int		extract_grid(char **lines, t_data *data, int start_idx);
int		validate_map(t_data *data);
int		find_player(t_data *data);

void	free_data(t_data *data);
void	free_split(char **split);
int		is_whitespace(char c);

#endif

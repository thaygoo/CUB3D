/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:43:15 by huburton          #+#    #+#             */
/*   Updated: 2026/02/23 15:43:15 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	**realloc_lines(char **lines, int count)
{
	char	**new_lines;
	int		i;

	new_lines = malloc(sizeof(char *) * (count + 2));
	if (!new_lines)
	{
		free_split(lines);
		return (NULL);
	}
	i = 0;
	if (lines)
	{
		while (i < count)
		{
			new_lines[i] = lines[i];
			i++;
		}
		free(lines);
	}
	new_lines[i] = NULL;
	new_lines[i + 1] = NULL;
	return (new_lines);
}

static char	**append_line(char **lines, char *line, int count)
{
	char	**new_lines;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_lines = realloc_lines(lines, count);
	if (!new_lines)
	{
		free(line);
		return (NULL);
	}
	new_lines[count] = line;
	return (new_lines);
}

char	**read_file_lines(char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines = append_line(lines, line, count);
		if (!lines)
		{
			close(fd);
			return (NULL);
		}
		count++;
	}
	close(fd);
	return (lines);
}

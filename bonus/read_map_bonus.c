/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:05:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/19 01:36:10 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	ft_add_line(char *line_read, t_vars *vars)
{
	char	**map_new;
	int		y;

	vars->map_hgt++;
	if (vars->map_hgt == 1)
		vars->map_wth = ft_strlen(line_read) - 1;
	map_new = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!map_new)
		return (ft_error("Malloc error", 1));
	y = -1;
	while (++y < vars->map_hgt - 1)
		map_new[y] = vars->map[y];
	map_new[y++] = line_read;
	map_new[y] = NULL;
	if (vars->map)
		free(vars->map);
	vars->map = map_new;
	return (true);
}

bool	ft_read_map(char *map_name, t_vars *vars)
{
	int		fd;
	char	*line_read;

	fd = open(map_name, O_RDONLY);
	if (fd <= -1)
		return (ft_error("Error opening the file", 1));
	line_read = get_next_line(fd);
	while (line_read)
	{
		if (ft_add_line(line_read, vars) == true)
			line_read = get_next_line(fd);
		else
		{
			if (line_read)
				free(line_read);
			line_read = get_next_line(-1);
			return (false);
		}
	}
	close(fd);
	return (true);
}

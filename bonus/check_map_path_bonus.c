/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_path_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:49:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/19 01:27:32 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

// added a line for Monster 'M'
static bool	ft_check_field(char c, t_vars *vars)
{
	if (c == '0')
		return (true);
	else if (c == '1' || c == 'M')
		return (false);
	else if (c == 'C' || c == 'E' || c == 'P')
		vars->amt_p_e_c++;
	else
		return (false);
	return (true);
}

//calls the check field function to validate that the position is valid
//then adds this position to the position_queue 
static bool	ft_do_direction(t_vars *vars, t_lst **pos_queue, int y, int x)
{
	t_lst	*temp;

	if (ft_check_field(vars->map_cpy[y][x], vars))
	{
		vars->map_cpy[y][x] = '1';
		temp = ft_new_node(y, x);
		if (!temp)
		{
			ft_clear_lst(pos_queue);
			return (ft_error("Malloc error", 1));
		}
		ft_node_add_back(pos_queue, temp);
	}
	return (true);
}

//checks from the position the positions next to it
//to find out if there is a valid path
static bool	ft_check_dir(t_vars *vars, int y, int x, t_lst **pos_queue)
{
	if (!(y < 0 || y >= vars->map_hgt || x < 0 || x >= vars->map_wth))
	{
		if (ft_do_direction(vars, pos_queue, y + 1, x) == false)
			return (false);
		if (ft_do_direction(vars, pos_queue, y - 1, x) == false)
			return (false);
		if (ft_do_direction(vars, pos_queue, y, x + 1) == false)
			return (false);
		if (ft_do_direction(vars, pos_queue, y, x - 1) == false)
			return (false);
	}
	return (true);
}

//iterates through all positions starting at the player position
//to find a connected path in the map
bool	ft_find_path(t_vars *vars)
{
	t_lst	*pos_queue;
	t_lst	*temp;

	pos_queue = ft_new_node(vars->p_pos_y, vars->p_pos_x);
	if (!pos_queue)
		return (ft_error("Malloc error", 1));
	while (pos_queue)
	{
		if (ft_check_dir(vars, pos_queue->y, pos_queue->x, &pos_queue) == false)
			return (false);
		temp = pos_queue;
		pos_queue = pos_queue->next;
		free(temp);
	}
	ft_clear_lst(&pos_queue);
	if (vars->amt_p + vars->amt_e + vars->amt_c != vars->amt_p_e_c)
		return (ft_error("No valid path", 1));
	return (true);
}

//creates a copy of the map
//this map is used to validate that there is a valid path
bool	ft_copy_map(t_vars *vars)
{
	int		y;

	vars->map_cpy = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!vars->map_cpy)
		return (ft_error("Malloc error", 1));
	y = 0;
	while (vars->map[y])
	{
		vars->map_cpy[y] = ft_strdup(vars->map[y]);
		if (!vars->map_cpy[y])
		{
			ft_free_map(vars, 1);
			return (ft_error("Malloc error", 1));
		}
		y++;
	}
	vars->map_cpy[y] = NULL;
	return (true);
}

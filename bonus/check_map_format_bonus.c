/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:58:13 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/19 01:26:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//modified for bonus -> added 'M' for monster
static bool	ft_valid_char(char c, t_vars *vars, int y, int x)
{
	if (c == '0' || c == '1' || c == 'M')
		return (true);
	else if (c == 'C')
		vars->amt_c++;
	else if (c == 'E' )
	{
		vars->exit_pos_y = y;
		vars->exit_pos_x = x;
		vars->amt_e++;
		if (vars->amt_e != 1)
			return (ft_error("Too many of E", 1));
	}
	else if (c == 'P')
	{
		vars->p_pos_y = y;
		vars->p_pos_x = x;
		vars->amt_p++;
		if (vars->amt_p != 1)
			return (ft_error("Too many of P", 1));
	}
	else
		return (ft_error("Invalid chars", 1));
	return (true);
}

static bool	ft_check_map_lines(t_vars *vars, int y, int x)
{
	while (vars->map[y])
	{
		x = 0;
		if (vars->map[y][x++] != '1')
			return (ft_error("Not surrounded by '1'", 1));
		while (vars->map[y][x] && vars->map[y][x] != '\n')
		{
			if (x == 0 || y + 1 == vars->map_hgt)
			{
				if (vars->map[y][x] != '1')
					return (ft_error("Not surrounded by '1'", 1));
			}
			else if (ft_valid_char(vars->map[y][x], vars, y, x) == false)
				return (false);
			x++;
		}
		if (x != vars->map_wth)
			return (ft_error("Not a rectangle", 1));
		if (vars->map[y][x - 1] != '1')
			return (ft_error("Not surrounded by '1'", 1));
		y++;
	}
	return (true);
}

bool	ft_check_map_chars(t_vars *vars)
{
	if (vars->map_wth < 3 || vars->map_hgt < 3)
		return (ft_error("Map too small", 1));
	if (ft_check_map_lines(vars, 0, 0) == false)
		return (false);
	if (vars->amt_e != 1 || vars->amt_p != 1 || vars->amt_c < 1)
		return (ft_error("Wrong ammount of E P or C", 1));
	return (true);
}

bool	ft_check_map_name(char *map_name)
{
	int	name_len;

	name_len = ft_strlen(map_name);
	if (name_len > 4)
	{
		if (ft_strncmp(map_name + (name_len - 4), ".ber", 4) == 0)
			return (true);
	}
	return (ft_error("Wrong map Name", 1));
}

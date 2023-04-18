/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:11:26 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/18 23:42:33 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// calculates the starting pov range for y
static void	ft_get_pov_range_y(t_vars *vars)
{
	if (vars->p_pos_y < vars->pov_u_max)
	{
		vars->pov_u = vars->p_pos_y;
		vars->pov_d = vars->pov_d_max + vars->pov_u_max - vars->pov_u;
	}
	else if (vars->map_hgt - vars->p_pos_y < vars->pov_d_max)
	{
		vars->pov_d = vars->map_hgt - vars->p_pos_y;
		vars->pov_u = vars->pov_d_max + vars->pov_u_max - vars->pov_d;
	}
	else
	{
		vars->pov_u = vars->pov_u_max;
		vars->pov_d = vars->pov_d_max;
	}
}

// calculates the starting pov range for x
static void	ft_get_pov_range_x(t_vars *vars)
{
	if (vars->p_pos_x < vars->pov_l_max)
	{
		vars->pov_l = vars->p_pos_x;
		vars->pov_r = vars->pov_r_max + vars->pov_l_max - vars->pov_l;
	}
	else if (vars->map_wth - vars->p_pos_x < vars->pov_r_max)
	{
		vars->pov_r = vars->map_wth - vars->p_pos_x;
		vars->pov_l = vars->pov_r_max + vars->pov_l_max - vars->pov_r;
	}
	else
	{
		vars->pov_l = vars->pov_l_max;
		vars->pov_r = vars->pov_r_max;
	}
}

// calculate pov values and window size
void	ft_get_pov_values(t_vars *vars, int *win_wth, int *win_hgt)
{
	if (vars->map_hgt * IMG_HGT < SCREEN_HGT - IMG_HGT)
	{
		*win_hgt = vars->map_hgt * IMG_HGT;
		vars->pov_u_max = vars->map_hgt;
	}
	else
		vars->pov_u_max = (*win_hgt / IMG_HGT) / 2;
	if (vars->map_wth * IMG_WTH < SCREEN_WTH - IMG_WTH)
	{
		*win_wth = vars->map_wth * IMG_WTH;
		vars->pov_l_max = vars->map_wth;
	}
	else
		vars->pov_l_max = (*win_wth / IMG_WTH) / 2;
	vars->pov_d_max = vars->pov_u_max;
	vars->pov_r_max = vars->pov_l_max;
	if (vars->pov_u_max + vars->pov_d_max < vars->map_hgt)
		ft_get_pov_range_y(vars);
	if (vars->pov_l_max + vars->pov_r_max < vars->map_wth)
		ft_get_pov_range_x(vars);
}

// calulates the new pov if the player moves.
// vars->pov_r < vars->pov_r_max || vars->pov_l < vars->pov_l_max || ->
// vars->pov_u < vars->pov_u_max || vars->pov_d < vars->pov_d_max || ->
// with these conditions the map only starts to move, if the player crosses
// the center of the pov
void	ft_change_pov_values_on_move(t_vars *vars, int y, int x)
{
	if (x != 0 && vars->pov_l_max + vars->pov_r_max < vars->map_wth)
	{
		if ((vars->pov_r < vars->pov_r_max || vars->pov_l < vars->pov_l_max
				|| vars->p_pos_x + vars->pov_r > vars->map_wth
				|| vars->p_pos_x - vars->pov_l < 0) && vars->pov_l + x >= 0)
		{
			vars->pov_l += x;
			vars->pov_r = vars->pov_r_max + (vars->pov_l_max - vars->pov_l);
		}
	}
	if (y != 0 && vars->pov_u_max + vars->pov_d_max < vars->map_hgt)
	{
		if ((vars->pov_u < vars->pov_u_max || vars->pov_d < vars->pov_d_max
				|| vars->p_pos_y + vars->pov_d > vars->map_hgt
				|| vars->p_pos_y - vars->pov_u < 0) && vars->pov_u + y >= 0)
		{
			vars->pov_u += y;
			vars->pov_d = vars->pov_d_max + (vars->pov_u_max - vars->pov_u);
		}
	}
}

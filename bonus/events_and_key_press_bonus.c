/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_and_key_press_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:17:56 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/24 22:21:44 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// added a line for monster to quit, when dying
static bool	ft_check_move(t_vars *vars, char *c)
{
	if (*c == '0')
		return (true);
	else if (*c == 'C')
	{
		vars->taken_c++;
		*c = '0';
	}
	else if (*c == 'M')
	{
		ft_put_movement_counter(vars, ++(vars->num_moves));
		ft_close_game(vars);
	}
	else if (*c == 'E')
	{
		if (vars->taken_c == vars->amt_c)
		{
			ft_put_movement_counter(vars, ++(vars->num_moves));
			ft_close_game(vars);
		}
		else
			*c = '0';
	}
	else
		return (false);
	return (true);
}

static bool	ft_mv_p(t_vars *vars, int y, int x)
{
	if (ft_check_move(vars, &vars->map[y][x]) == false)
		return (false);
	vars->num_moves++;
	ft_swap(&vars->map[vars->p_pos_y][vars->p_pos_x], &vars->map[y][x]);
	if (vars->exit_pos_y == vars->p_pos_y && vars->exit_pos_x == vars->p_pos_x)
		vars->map[vars->exit_pos_y][vars->exit_pos_x] = 'E';
	vars->p_pos_y = y;
	vars->p_pos_x = x;
	return (true);
}

int	ft_key_press(int key, t_vars *vars)
{
	if (key == arrow_u && ft_mv_p(vars, vars->p_pos_y - 1, vars->p_pos_x))
		ft_change_pov_values_on_move(vars, -1, 0);
	else if (key == arrow_d && ft_mv_p(vars, vars->p_pos_y + 1, vars->p_pos_x))
		ft_change_pov_values_on_move(vars, 1, 0);
	else if (key == arrow_l && ft_mv_p(vars, vars->p_pos_y, vars->p_pos_x - 1))
		ft_change_pov_values_on_move(vars, 0, -1);
	else if (key == arrow_r && ft_mv_p(vars, vars->p_pos_y, vars->p_pos_x + 1))
		ft_change_pov_values_on_move(vars, 0, 1);
	else if (key == esc)
		ft_close_game(vars);
	else
		return (1);
	if (vars->win_ptr)
		ft_render_pov(vars);
	return (0);
}

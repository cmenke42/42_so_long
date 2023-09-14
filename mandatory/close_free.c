/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:17:10 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/27 19:52:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_window_x(t_vars *vars)
{
	ft_close_game(vars);
	return (0);
}

void	ft_free_map(t_vars *vars, int map)
{
	int	y;

	y = 0;
	if (map == 0 && vars->map)
	{
		while (vars->map[y])
			free(vars->map[y++]);
		free(vars->map);
	}
	else if (map == 1 && vars->map_cpy)
	{
		while (vars->map_cpy[y])
			free(vars->map_cpy[y++]);
		free(vars->map_cpy);
	}
}

bool	ft_destroy_mlx_images(t_vars *vars)
{
	if (vars->path_img)
		mlx_destroy_image(vars->mlx_ptr, vars->path_img);
	if (vars->wall_img)
		mlx_destroy_image(vars->mlx_ptr, vars->wall_img);
	if (vars->player_img)
		mlx_destroy_image(vars->mlx_ptr, vars->player_img);
	if (vars->collect_img)
		mlx_destroy_image(vars->mlx_ptr, vars->collect_img);
	if (vars->exit_img)
		mlx_destroy_image(vars->mlx_ptr, vars->exit_img);
	return (false);
}

void	ft_close_game(t_vars *vars)
{
	int	exit_code;

	exit_code = vars->exit_code;
	ft_destroy_mlx_images(vars);
	if (vars->mlx_ptr && vars->win_ptr)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	ft_free_map(vars, 0);
	free(vars);
	exit(exit_code);
}
